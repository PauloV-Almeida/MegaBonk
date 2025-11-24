#include "../include/Projetil.h"
#include "../include/GerenciadorColisoes.h"

namespace Entidades
{
	Projetil::Projetil(bool alv, sf::Vector2f pos, sf::Vector2f velocity, float dmg, float radius, float lftm, bool ativo) :
		Entidade(4, velocity),
		tempoVida(static_cast<int>(lftm)),
		corpo(sf::Vector2f(radius * 2, radius * 2)),
		ativo(ativo),
		dano(static_cast<int>(dmg)),
		vivo(alv)
	{
		corpo.setPosition(pos);
		
	}
	Projetil::~Projetil()
	{
	}
	void Projetil::executar()
	{
		if (vivo) 
		{
			mover();
			tempoVida--;

			if (tempoVida <= 0)
			{
				vivo = false;
			}
		}
		
	}
	

}