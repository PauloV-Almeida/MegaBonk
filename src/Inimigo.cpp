#include "../include/Inimigo.h"

namespace Entidades
{
	namespace Personagens
	{
		Inimigo::Inimigo(int indice, sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f tam) :
			Personagem(indice, pos, vel, tam)
		{
			dano = 0;
		}
		Inimigo::~Inimigo()
		{
		}
		
		Inimigo::mover()
		{
			vel.y += GRAVIDADE;
			corpo.setPosition(corpo.getPosition() + vel);
		}	
	}
}