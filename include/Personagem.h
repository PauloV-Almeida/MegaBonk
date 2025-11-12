#pragma once

#include "Entidades.h"

namespace Entidades
{
	namespace Personagens
	{
		class Personagem : public Entidade
		{
		protected:
			int num_vidas;
			sf::RectangleShape corpo;
			sf::Vector2f velocidade;
		public:
			Personagem(const sf::Vector2f pos, const sf::Vector2f vel, const sf::Vector2f tam);
			Personagem();
			~Personagem();
			const sf::RectangleShape getCorpo();
			void setColor(sf::Color cor);
			void salvarDataBuffer();
			virtual void executar() = 0;
			virtual void mover() = 0;
		};
	}
}