#include "../include/Entidades.h"


int Entidades::Entidade::contar(0);
float Entidades::Entidade::velocidade(10.f);

sf::Vector2f Entidades::Entidade::posJogador(200.f, 200.f);

namespace Entidades
{				
	Entidade::Entidade(int indice, sf::Vector2f velo):
		Ente(),
		id(indice),
		gColisoes(nullptr),
		vel(velo)
	{
	
	}

	Entidade::~Entidade()
	{
	}
}
