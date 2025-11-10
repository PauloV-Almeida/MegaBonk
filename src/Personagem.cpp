#include "../include/Personagem.h"

namespace Entidades
{
	namespace Personagens 
	{
		Personagem::Personagem(int indice, sf::Vector2f pos, sf::Vector2f velo, sf::Vector2f tamanho) :
			Entidade(indice, velo),
			corpo(tamanho),
			life(1)
		{
			//tenho que inicializar a posicao do corpo
			
		}
		Personagem::~Personagem()
		{
		}

		void Personagem::desenhar()
		{
			pGG->desenhar(&corpo);
		}
	}
}