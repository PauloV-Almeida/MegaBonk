#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <string>

#include "Personagem.h"

namespace Entidades
{
	namespace Personagens
	{
		class Jogador : public Personagem
		{
		private:

			int player_id;

		public:
			Jogador(int index = 1, sf::Vector2f pos = sf::Vector2f(10.f, 0.f), sf::Vector2f velo = sf::Vector2f(0.f, 0.f), sf::Vector2f tamanho = sf::Vector2f(50.f, 50.f));
			Jogador(int index,int vida, sf::Vector2f pos, sf::Vector2f velo, sf::Vector2f tamanho);
			~Jogador();
			
			void executar();
			void mover(char direcao = '0');


			void desenhar();
		};
	}
}