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

		std::srand(std::time(nullptr));
		if (vivo != 0 && vivo != 1)
			vivo = std::rand() % vivo;

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
		if (aux)
		{
			Entidades::Entidade* pIni = nullptr;
			pIni = static_cast<Entidades::Entidade*>(aux);
			pIni->set_GerenciadorColisao(&gColisoes);
			inimigos.add(pIni);
		}
		return static_cast<Entidades::Entidade*>(aux);
	}
	void Fase::criarCenario(std::string arquivo)
	{
		std::ifstream entrada(arquivo);

		// CORREÇÃO: testar se o arquivo NÃO abriu
		if (!entrada)
		{
			std::cout << "Arquivo não encontrado: " << arquivo << std::endl;
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
					break;
				default:

					break;
				}
				j++;
			}
		}
		entrada.close();
	}//cenario


}