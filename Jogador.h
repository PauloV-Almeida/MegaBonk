#pragma once

#include "../MegaBonk/Personagem.h"


namespace Entidades
{
	namespace Personagens
	{
		class Inimigo;

		class Jogador :public Personagem
		{
		protected:
			int pontos;
		public:
			Jogador(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f tam);
			Jogador();
			~Jogador();
			void mover();
			void colidir(Inimigo* pIn);
			void executar();
			void salvar();
			
		};
	}
}