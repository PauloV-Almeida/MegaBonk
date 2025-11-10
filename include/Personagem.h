#pragma once

#include "Entidades.h"

namespace Entidades
{
	namespace Personagens
	{
		class Personagem : public Entidade
		{
		protected:
			sf::RectangleShape corpo;
			int life;
		public:
			Personagem(int indice = -1, sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Vector2f velo = sf::Vector2f(0.f, 0.f), sf::Vector2f tamanho = sf::Vector2f(0.f, 0.f));
			virtual ~Personagem();
			virtual void executar() = 0;
			//virtual void collide(Entity* other, std::string direction = "") = 0;
			//void inflict_damage(int dmg) { life -= dmg; }
			//void set_alive(bool a) { alive = a; }
			virtual void desenhar();
			sf::Vector2f get_posicao() { return corpo.getPosition(); }
			sf::Vector2f get_Tamanho() { return corpo.getSize(); }
			void set_posicao(sf::Vector2f pos) { corpo.setPosition(pos); }
			//const bool get_alive() const { return alive; }
			const int get_life() const { return life; }
		};
	}
}