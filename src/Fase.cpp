#include "../include/Fase.h"

namespace Fases
{
	Fase::Fase(int id) :
		Estados::Estado(id),
		jogadores(),
		inimigos(),
		obstaculos(),
		gColisoes(),
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
		Entidades::Entidade* aux = nullptr;
		int indice, vivo, vida;
		std::string linha;
		float px, py, vx, vy, dano, sx, sy;
		arquivo >> indice >> vivo >> vida >> dano >> px >> py >> vx >> vy;

		std::srand(std::time(nullptr));//aleatoriedade
		if (vivo != 0 && vivo != 1)
		{
			vivo = std::rand() % vivo;
		}
		switch (indice)
		{
		case 1:
			int emp;
			arquivo >> sx >> sy >> emp;
			aux = new Entidades::Personagens::Esqueleto(((bool)vivo), vida, sf::Vector2f(px, py), sf::Vector2f(vx, vy), dano, sf::Vector2f(sx, sy), emp);
			break;
		default:
			break;
		}
		aux->set_GerenciadorColisao(&gColisoes);

		Entidades::Entidade* inimigo = nullptr;
		inimigo = static_cast<Entidades::Entidade*>(aux);
		if (inimigo)
		{
			inimigo->set_GerenciadorColisao(&gColisoes);
			inimigos.add(inimigo);
		}
		return static_cast<Entidades::Entidade*>(aux);
		
	}
	void Fase::criarCenario(std::string arquivo, std::string save)
	{
		std::ifstream entrada(arquivo);
		std::ofstream saida(save);

		// CORREÇÃO: testar se o arquivo NÃO abriu
		if (!entrada)
		{
			std::cout << "Arquivo não encontrado: " << arquivo << std::endl;
			exit(1);
		}

		if(!saida)
		{
			std::cout << "Não foi possível criar o arquivo de salvamento: " << save << std::endl;
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
						obstaculos.add(pObs);
					}
					saida << 0;
					break;
				default:
					saida << ' ';
					break;
				}
				j++;
			}
		}
		entrada.close();
		saida.close();
	}//cenario

	void Fase::carregaCenario(std::string saveCenarioArq)
	{
		if(obstaculos.get_tamanho() > 0)
			obstaculos.limpar();

		std::ifstream entrada(saveCenarioArq);

		if(!entrada)
		{
			std::cout << "Arquivo de salvamento do cenario não encontrado: " << saveCenarioArq << std::endl;
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
						obstaculos.add(pObs);
					}
					break;
				default:
					break;
				}
				j++;
			}
			entrada.close();
		}
	}//carregaCenario
}