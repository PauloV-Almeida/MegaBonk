#include "../include/Deserto.h"
#include <limits>
#include <cstdlib>
#include <ctime>
#include <vector>

namespace Fases
{
	Deserto::Deserto() :
		Fase(1),
		fim(0)
	{
		corpo.setSize(sf::Vector2f(900.f, 600.f));
		texturas = pGG->carregar_texturas("./assets/Deserto.png");
		corpo.setTexture(texturas);

	}

	Deserto::Deserto(int n_jogadores) :
		Fase(6),
		fim(TEMPOFIM)
	{
		corpo.setSize(sf::Vector2f(900.f, 600.f));
		texturas = pGG->carregar_texturas("./assets/Deserto.png");
		corpo.setTexture(texturas);

	}

	Deserto::~Deserto()
	{
		if (carregado)
		{
			salvar();
		}
	}

	void Deserto::executar()
	{
		if (!carregado)
		{
			carregar();
		}

		jogadores.executar();
		obstaculos.executar();
		inimigos.executar();

		gColisoes.executar();

		// Transição automática para próxima fase quando não houver inimigos
		// Ajuste NEXT_STATE_ID para o ID real da próxima fase, se necessário.
		const int NEXT_STATE_ID = id_estado + 1;
		if (inimigos.get_tamanho() == 0)
		{
			std::cerr << "[Deserto::executar] todos inimigos mortos -> mudando para fase ID=" << NEXT_STATE_ID << std::endl;
			pEG->set_AtualEstado(NEXT_STATE_ID);
			pEG->reseta_AtualEstado();
			return; // evita continuar execução desta fase
		}

		desenhar();

		if (pEG->get_AtualEstadoID() == id_estado)
		{
			Listas::Lista<Entidades::Entidade>::Iterator<Entidades::Entidade> it = jogadores.get_Primeiro();
			Entidades::Personagens::Jogador* p1 = dynamic_cast<Entidades::Personagens::Jogador*>(*it);
			it++;

			if (jogadores.get_tamanho() == 1)
			{
				if (p1->get_venceu())
				{
					p1->set_venceu(false);
					pEG->set_AtualEstado(2);
					pEG->reseta_AtualEstado();
				}
				if ((*jogadores.get_Primeiro())->get_vivo())
				{
					(*jogadores.get_Primeiro())->get_posicao();
				}
				else
				{
					pEG->set_AtualEstado(3);
					pEG->reseta_AtualEstado();
				}
			}
			else
			{
				Entidades::Personagens::Jogador* p2 = dynamic_cast<Entidades::Personagens::Jogador*>(*it);
				if (p1->get_venceu() || p2->get_venceu())
				{
					if (fim == 400)
					{
						p1->set_venceu(false);
						p2->set_venceu(false);

					}
					fim--;
				}
				if (fim < 0)
				{
					pEG->set_AtualEstado(2);
					pEG->reseta_AtualEstado();
				}
				else
				{
					if (!(*jogadores.get_Primeiro())->get_vivo() && !(*it)->get_vivo())
					{
						pEG->set_AtualEstado(3);
						pEG->reseta_AtualEstado();
					}
				}

				if (fim < TEMPOFIM)
					fim--;
			}

		}
		jogadores.desenhar();
		std::cerr << "[Deserto::executar] inimigos.get_tamanho()=" << inimigos.get_tamanho() << std::endl;
		auto it = inimigos.get_Primeiro();
		int idx = 0;
		while (it != nullptr) {
			Entidades::Entidade* e = *it;
			std::cerr << "  inimigo[" << idx++ << "] ptr=" << e;
			auto pini = dynamic_cast<Entidades::Personagens::Inimigo*>(e);
			std::cerr << " isInimigo=" << (pini != nullptr);
			if (e) {
				std::cerr << " pos=(" << e->get_posicao().x << "," << e->get_posicao().y << ") tam=(" << e->get_tamanho().x << "," << e->get_tamanho().y << ")";
				std::cerr << " vivo=" << (e->get_vivo() ? 1 : 0);
			}
			std::cerr << std::endl;
			it++;
		}
		inimigos.desenhar();
		obstaculos.desenhar();
	}//executar

	void Deserto::salvar()
	{
		std::ofstream jogadoresArq;
		std::ofstream inimigosArq;

		if (id_estado == 1)
		{
			jogadoresArq.open(ARQ_JOGADOR11);
			inimigosArq.open(ARQ_INIMIGOS11);
		}
		else if (id_estado == 6)
		{
			jogadoresArq.open(ARQ_JOGADOR12);
			inimigosArq.open(ARQ_INIMIGOS12);
		}

		if (!jogadoresArq)
		{
			std::cerr << "ERRO ARQUIVO JOGADOR\n";
			exit(1);
		}

		jogadoresArq << jogadores.get_tamanho() << std::endl;
		//jogadores.salvar(jogadoresArq);
		jogadoresArq.close();

		if (!inimigosArq)
		{
			std::cerr << "ERRO ARQUIVO INIMIGOS\n";
			exit(1);
		}
		inimigosArq << inimigos.get_tamanho() << std::endl;
		//inimigos.salvar(inimigosArq);
		inimigosArq.close();
	}
	void Deserto::carregar()
	{
		// carrega cenário (obstáculos) primeiro
		carregaCenario(SALVAR_CENARIO_1);

		int n, vivo, dano, vida;
		float vx, vy, px, py, tamx, tamy;
		std::string linha;
		std::ifstream jogadoresArq;
		std::ifstream inimigosArq;

		if (id_estado == 1)
		{
			jogadoresArq.open(ARQ_JOGADOR11);
			inimigosArq.open(ARQ_INIMIGOS11);
		}
		else if (id_estado == 6)
		{
			jogadoresArq.open(ARQ_JOGADOR12);
			inimigosArq.open(ARQ_INIMIGOS12);
		}
		if (!jogadoresArq)
		{
			std::cerr << "ERRO ARQUIVO JOGADOR\n";
			exit(1);
		}
		jogadoresArq >> n;

		// Carregar jogadores (como antes) ...
		jogadoresArq >> std::ws;
		if (jogadoresArq.peek() == EOF)
		{
			for (int i = 0; i < n; i++)
			{
				vivo = 1; vida = 100; px = 50.f + i * 50.f; py = 50.f; vx = vy = 0.f; tamx = tamy = 32.f;
				Entidades::Personagens::Jogador* pJog = new Entidades::Personagens::Jogador(i + 1, vivo, vida, sf::Vector2f(px, py), sf::Vector2f(vx, vy), sf::Vector2f(tamx, tamy));
				Entidades::Entidade* jogador = pJog;
				if (jogador)
				{
					jogadores.add(jogador);
					jogador->set_GerenciadorColisoes(&gColisoes);
				}
			}
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				if (!(jogadoresArq >> vivo >> vida >> px >> py >> vx >> vy >> tamx >> tamy))
				{
					vivo = 1; vida = 100; px = 50.f + i * 50.f; py = 50.f; vx = vy = 0.f; tamx = tamy = 32.f;
				}
				Entidades::Personagens::Jogador* pJog = new Entidades::Personagens::Jogador(i + 1, vivo, vida, sf::Vector2f(px, py), sf::Vector2f(vx, vy), sf::Vector2f(tamx, tamy));
				Entidades::Entidade* jogador = pJog;
				if (jogador)
				{
					jogadores.add(jogador);
					jogador->set_GerenciadorColisoes(&gColisoes);
				}
			}
		}

		if (!inimigosArq)
		{
			std::cerr << "ERRO ARQUIVO INIMIGOS\n";
			exit(1);
		}

		// lê número de inimigos
		inimigosArq >> n;
		std::cerr << "[Deserto::carregar] n lido do arquivo de inimigos = " << n
			<< " fail=" << std::boolalpha << inimigosArq.fail() << std::noboolalpha << std::endl;

		// debug: se n <= 0, mostre conteúdo do arquivo para entender formato
		if (n <= 0)
		{
			std::cerr << "[Deserto::carregar] arquivo de inimigos vazio ou formato diferente. Conteúdo do arquivo:" << std::endl;
			// reposiciona no início e imprime linhas
			inimigosArq.clear();
			inimigosArq.seekg(0);
			while (std::getline(inimigosArq, linha))
			{
				std::cerr << "  '" << linha << "'" << std::endl;
			}
			// não retorna aqui: continuamos e, abaixo, garantimos fallback se lista final ficar vazia
		}

		// consumir newline pendente antes de getline em criarEsqueleto
		inimigosArq.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		// limpar listas e recriar
		inimigos.limpar();
		gColisoes.limparInimigos();

		for (int i = 0; i < n; i++)
		{
			criarEsqueleto(inimigosArq);
		}

		// garantir registro dos inimigos
		gColisoes.incluirInimigos(&inimigos);

		// SE AINDA NÃO HOUVE INIMIGOS, criar fallback em posições fixas no chão
		if (inimigos.get_tamanho() == 0)
		{
			std::vector<sf::Vector2f> fixedPositions = {
				sf::Vector2f(150.f, 400.f), // y perto do chão da cena (900x600 -> y ~600 - altura_sprite)
				sf::Vector2f(300.f, 450.f),
				sf::Vector2f(450.f, 300.f),
				sf::Vector2f(600.f, 380.f),
				sf::Vector2f(750.f, 600.f)
			};

			std::cerr << "[Deserto::carregar] fallback final: criando " << fixedPositions.size() << " esqueletos em posições fixas." << std::endl;
			for (const auto& pos : fixedPositions)
			{
				Entidades::Personagens::Esqueleto* fallback = new Entidades::Personagens::Esqueleto(true, 10, pos, sf::Vector2f(0.f, 0.f), 1.0f, sf::Vector2f(32.f, 32.f), 1.0f);
				if (fallback)
				{
					fallback->set_GerenciadorColisoes(&gColisoes);
					inimigos.add(static_cast<Entidades::Entidade*>(fallback));
					Entidades::Personagens::Inimigo* pIni = dynamic_cast<Entidades::Personagens::Inimigo*>(fallback);
					if (pIni) gColisoes.adicionarInimigo(pIni);
					std::cerr << "[Deserto::carregar] fallback esqueleto adicionado ptr=" << fallback << " pos=(" << pos.x << "," << pos.y << ")\n";
				}
			}
		}

		carregado = true;
	}

	void Deserto::resetar()
	{
		criarCenario(ARQUIVO_CENARIO_1, SALVAR_CENARIO_1);

		// limpar sempre antes de repopular para evitar resíduos
		jogadores.limpar();
		inimigos.limpar();
		gColisoes.limparInimigos();
		gColisoes.limparObstaculos();

		int n, vivo, dano, vida, vx, vy, px, py, tamx, tamy;
		std::string linha;

		std::ifstream jogadoresArq;
		std::ifstream inimigosArq;
		if (id_estado == 1)
		{
			jogadoresArq.open(RESET_ARQ_JOG11);
			inimigosArq.open(RESET_ARQ_INI11);
		}
		else if (id_estado == 6)
		{
			jogadoresArq.open(RESET_ARQ_JOG12);
			inimigosArq.open(RESET_ARQ_INI12);
		}
		if (!jogadoresArq)
		{
			std::cerr << "ERRO ARQUIVO JOGADOR\n";
			exit(1);
		}
		jogadoresArq >> n;
		for (int i = 0; i < n; i++)
		{
			jogadoresArq >> vivo >> vida >> px >> py >> vx >> vy >> tamx >> tamy;
			Entidades::Personagens::Jogador* pJog = new Entidades::Personagens::Jogador(i + 1, vivo, vida, sf::Vector2f(px, py), sf::Vector2f(vx, vy), sf::Vector2f(tamx, tamy));
			Entidades::Entidade* jogador = pJog;
			if (jogador)
			{
				jogadores.add(jogador);
				jogador->set_GerenciadorColisoes(&gColisoes);
			}
		}
		if (!inimigosArq)
		{
			std::cerr << "ERRO ARQUIVO INIMIGOS\n";
			exit(1);
		}
		inimigosArq >> n;
		for (int i = 0; i < n; i++)
		{
			getline(inimigosArq, linha); // consumir a quebra de linha restante
			criarEsqueleto(inimigosArq);
		}

		// garantir registro dos inimigos no gerenciador de colisões
		gColisoes.incluirInimigos(&inimigos);
		carregado = true;
	}
}