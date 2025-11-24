#include "../include/Inimigo.h"

namespace Entidades
{
	namespace Personagens
	{
		Inimigo::Inimigo(int indice, sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f tam) :
			Personagem(indice, pos, vel, tam),
			nivel_maldade(0)
		{
			
		}
		Inimigo::~Inimigo()
		{
		}
		
		void Inimigo::executar()
		{
			mover();
			if(vivo && n_vidas < 0)
				vivo = false;
		}
		
		void Inimigo::mover()
		{
			
		}
		
		
	}
}