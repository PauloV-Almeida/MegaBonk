#include "../include/Fase.h"
#include <sstream>
#include <iostream>

namespace Fases
{
	Fase::Fase(int id) :
		Estados::Estado(id),
		jogadores(),
		inimigos(),
		obstaculos(),
		gColisoes(),
		n_nasceu(0),
		carregado(false),
		corpo()
	{
		gColisoes.incluirJogadores(&jogadores);
		gColisoes.incluirInimigos(&inimigos);
		gColisoes.incluirObstaculos(&obstaculos);

		pGE = Gerenciadores::GerenciadorEventos::get_instance();
	}

	Fase::~Fase()
	{
	}

	void Fase::desenhar()
	{
		pGG->desenhar(&(this)->corpo);
	}

	Entidades::Entidade* Fase::criarEsqueleto(std::ifstream& arquivo)
	{
		// lê uma linha inteira do arquivo e faz parsing com istringstream -> mais robusto que >> isolado
		std::string linha;
		if (!std::getline(arquivo, linha)) {
			std::cerr << "[Fase::criarEsqueleto] falha ao ler linha (EOF ou erro de I/O)\n";
			return nullptr;
		}

		// ignora linhas vazias
		if (linha.empty()) {
			std::cerr << "[Fase::criarEsqueleto] linha vazia lida\n";
			return nullptr;
		}

		std::istringstream iss(linha);
		Entidades::Entidade* aux = nullptr;

		int indice;
		int vivo;
		int vida;
		float dano, px, py, vx, vy;

		if (!(iss >> indice >> vivo >> vida >> dano >> px >> py >> vx >> vy)) {
			std::cerr << "[Fase::criarEsqueleto] parse inicial falhou. linha: \"" << linha << "\"\n";
			return nullptr;
		}

		switch (indice)
		{
		case 1:
		{
			float sx, sy;
			int emp;
			if (!(iss >> sx >> sy >> emp)) {
				std::cerr << "[Fase::criarEsqueleto] parse params esqueleto (sx,sy,emp) falhou. linha: \"" << linha << "\"\n";
				// ainda assim podemos tentar criar com tamanhos/padrões para não perder o spawn
				sx = 32.f; sy = 32.f; emp = 0;
			}
			aux = new Entidades::Personagens::Esqueleto(
				static_cast<bool>(vivo),
				vida,
				sf::Vector2f(px, py),
				sf::Vector2f(vx, vy),
				dano,
				sf::Vector2f(sx, sy),
				emp
			);
			break;
		}
		default:
			std::cerr << "[Fase::criarEsqueleto] indice desconhecido lido: " << indice << " linha: \"" << linha << "\"\n";
			break;
		}

		if (aux)
		{
			// Forçar inicialização segura: posição, velocidade zero, vivo = true e parado para evitar movimento indesejado.
			// Essas chamadas assumem que as implementações concretas (Esqueleto/Inimigo) expõem esses setters.
			try {
				aux->set_GerenciadorColisoes(&gColisoes);

				// Garanta posição inicial coerente
				aux->set_posicao(sf::Vector2f(px, py));

				// Zera velocidade e marca como parado (evita gravidade/movimento automático)
				aux->set_vel(sf::Vector2f(0.f, 0.f));
				aux->set_parado(true);

				// Garante que está vivo para ser desenhado
				aux->set_vivo(true);
			}
			catch (...) {
				// Caso alguma implementação não exponha os métodos esperados, apenas continue.
				// Não interrompe criação; deixamos logs para inspeção.
				std::cerr << "[Fase::criarEsqueleto] warning: não foi possível aplicar valores seguros a aux=" << aux << std::endl;
			}

			Entidades::Entidade* inimigo = static_cast<Entidades::Entidade*>(aux);
			inimigos.add(inimigo);

			Entidades::Personagens::Inimigo* pIni = dynamic_cast<Entidades::Personagens::Inimigo*>(aux);
			if (pIni) {
				gColisoes.adicionarInimigo(pIni);
			}
			else {
				std::cerr << "[Fase::criarEsqueleto] dynamic_cast<Inimigo*> falhou para ptr=" << aux << std::endl;
			}
		}
		else {
			std::cerr << "[Fase::criarEsqueleto] nenhum inimigo criado para linha: \"" << linha << "\"\n";
		}

		return aux;
	}

	void Fase::criarCenario(std::string arquivo, std::string save)
	{
		std::ifstream entrada(arquivo);
		std::ofstream saida(save);

		// CORRE��O: testar se o arquivo N�O abriu
		if (!entrada)
		{
			std::cout << "Arquivo n�o encontrado: " << arquivo << std::endl;
			exit(1);
		}

		if (!saida)
		{
			std::cout << "N�o foi poss�vel criar o arquivo de salvamento: " << save << std::endl;
			exit(1);
		}

		std::string linha;
		Entidades::Entidade* aux = nullptr;
		int j = 0;
		std::srand(std::time(nullptr));
		int n_ale = 0;
		for (int i = 0; std::getline(entrada, linha); i++)
		{
			j = 0;
			for (char character : linha)
			{
				switch (character)
				{
				case '0':
					aux = new Entidades::Obstaculos::Plataforma(sf::Vector2f(j * OBSTACULO_TAMANHO, i * OBSTACULO_TAMANHO));
					if (aux)
					{
						Entidades::Entidade* pObs = nullptr;
						pObs = static_cast<Entidades::Entidade*>(aux);
						if (pObs) {
							pObs->set_GerenciadorColisoes(&gColisoes);
							obstaculos.add(pObs);
							Entidades::Obstaculos::Obstaculo* pob = dynamic_cast<Entidades::Obstaculos::Obstaculo*>(pObs);
							if (pob) gColisoes.adicionarObstaculo(pob);
						}

					}
					saida << '0';
					break;
				case '1':
					aux = new Entidades::Obstaculos::Gosma(sf::Vector2f(j * OBSTACULO_TAMANHO, i * OBSTACULO_TAMANHO));
					if (aux)
					{
						Entidades::Entidade* pObs = nullptr;
						pObs = static_cast<Entidades::Entidade*>(aux);
						if (pObs) {
							pObs->set_GerenciadorColisoes(&gColisoes);
							obstaculos.add(pObs);
							Entidades::Obstaculos::Obstaculo* pob = dynamic_cast<Entidades::Obstaculos::Obstaculo*>(pObs);
							if (pob) gColisoes.adicionarObstaculo(pob);
						}
					}
					saida << '1';
					break;
				default:
					saida << ' ';
					break;
				}
				j++;
			}
			// adicionar quebra de linha para preservar o layout original
			saida << '\n';
		}
		entrada.close();
		saida.close();
	}//cenario

	void Fase::carregaCenario(std::string saveCenarioArq)
	{
		// remove obstáculos antigos da lista de entidades e do gerenciador de colisões
		if (obstaculos.get_tamanho() > 0)
		{
			obstaculos.limpar();
			gColisoes.limparObstaculos(); // requer método limparObstaculos no GerenciadorColisoes
		}

		std::ifstream entrada(saveCenarioArq);

		if (!entrada)
		{
			std::cout << "Arquivo de salvamento do cenario n�o encontrado: " << saveCenarioArq << std::endl;
			exit(1);
		}

		std::string linha;
		Entidades::Entidade* aux = nullptr;
		int j = 0;
		for (int i = 0; std::getline(entrada, linha); i++)
		{
			j = 0;
			for (char character : linha)
			{
				switch (character)
				{
				case '0':
					aux = new Entidades::Obstaculos::Plataforma(sf::Vector2f(j * OBSTACULO_TAMANHO, i * OBSTACULO_TAMANHO));
					if (aux)
					{
						Entidades::Entidade* pObs = nullptr;
						pObs = static_cast<Entidades::Entidade*>(aux);
						if (pObs) {
							pObs->set_GerenciadorColisoes(&gColisoes);
							obstaculos.add(pObs);
							Entidades::Obstaculos::Obstaculo* pob = dynamic_cast<Entidades::Obstaculos::Obstaculo*>(pObs);
							if (pob) gColisoes.adicionarObstaculo(pob);
						}
					}
					break;
				case '1':
					aux = new Entidades::Obstaculos::Gosma(sf::Vector2f(j * OBSTACULO_TAMANHO, i * OBSTACULO_TAMANHO));
					if (aux)
					{
						Entidades::Entidade* pObs = nullptr;
						pObs = static_cast<Entidades::Entidade*>(aux);
						if (pObs) {
							pObs->set_GerenciadorColisoes(&gColisoes);
							obstaculos.add(pObs);
							Entidades::Obstaculos::Obstaculo* pob = dynamic_cast<Entidades::Obstaculos::Obstaculo*>(pObs);
							if (pob) gColisoes.adicionarObstaculo(pob);
						}
					}
					break;
				default:
					break;
				}
				j++;
			}
		}
		// fechar arquivo ap�s terminar a leitura
		entrada.close();
	}//carregaCenario
}