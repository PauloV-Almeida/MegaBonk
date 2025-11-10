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
		
		
	}
}