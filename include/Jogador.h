#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <string>

#include "Personagem.h"

namespace Entidades
{
	namespace Personagens
	{
		class Inimigo;

		class Jogador : public Personagem
		{
		protected:
			int pontos;
		public:
			Jogador(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f tam);
			Jogador();
			~Jogador();
			void mover();
			void colidir(Inimigo* pIn) { num_vidas--; };
			void executar();
			void salvar() {};
			void colidir(Entidade* outro, std::string  direcao = "") {}
			void desenhar();
			sf::Vector2f get_posicao() { return corpo.getPosition(); }
			sf::Vector2f get_tamanho() { return corpo.getSize(); }
			void set_vivo(bool a) { if (!a) num_vidas = 0; }
			void set_posicao(sf::Vector2f pos) { corpo.setPosition(pos); }
			virtual void infligir_dano(int dmg) {}
		};
	}
}