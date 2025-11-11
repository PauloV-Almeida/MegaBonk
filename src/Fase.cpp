#include "../include/Fase.h"

namespace Fases
{
	Fase::Fase(int id) :
		jogadores(),
		inimigos(),
		corpo()
	{
		
	}
	Fase::~Fase()
	{
	}
	
	void Fase::desenhar()
	{
		pGG->desenhar(&(this->corpo));
		
	}

	void Fase::add_jogador(Entidades::Entidade* jogador)
	{
		if (jogador)
		{
			jogadores.add(jogador);
		}
	}
    void Fase::criar_scenario(std::string arquivo)
	{
		std::ifstream entrada(arquivo);
		
		if(!entrada)
		{ 
			std::cout << "Erro ao abrir o arquivo de cenário: " << arquivo << std::endl;
			exit(1);
		}

		std::string linha;
		Entidades::Entidade* aux = nullptr;
		int j = 0;
		
		std::srand(std::time(nullptr));
		int n_aleatorio = 0;

		for(int i=0; std::getline(entrada, linha); i++)
		{
			j = 0;
			for (char character : linha)
			{
				switch (character)
				{
				case '0':
					//aux = new Entidades::Obstaculos::Plataforma(sf::Vector2f(j * OBSTACULO_TAMANHO, i * OBSTACULO_TAMANHO));
				default:
					break;
				}
				j++;
			}	
		}
		entrada.close();
		
	}
}
