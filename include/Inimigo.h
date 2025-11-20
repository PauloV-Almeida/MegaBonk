#pragma once

#include "Personagem.h"
#include "Jogador.h"
namespace Entidades
{
	namespace Personagens
	{
		class Inimigo :public Personagem
		{
		protected:
			int nivel_maldade;
		public:
			Inimigo(int indice = -1,sf::Vector2f pos = sf::Vector2f(10.f, 0.f), sf::Vector2f vel = sf::Vector2f(0.f, 0.f), sf::Vector2f tam = sf::Vector2f(50.f, 50.f));
			~Inimigo();
			virtual void executar()= 0;
			virtual void danificar() = 0;
		};
	}
}