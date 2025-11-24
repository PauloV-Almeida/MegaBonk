#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <string>

#include "Personagem.h"

#define DELAY_ATAQUE 30
#define RECUO 5
#define DMG 3


namespace Entidades
{
	namespace Personagens
	{
		class Jogador : public Personagem
		{
		protected:
			sf::RectangleShape ataque_corpo;
			bool atacando;
			int delay_ataque;
			int id_jogador;
			bool venceu;
			bool direita;
			std::string ataque_direcao;
			int dano_ataque;
		public:
			Jogador(int indice = 1, sf::Vector2f pos = sf::Vector2f(10.f, 0.f), sf::Vector2f vel = sf::Vector2f(0.f, 0.f), sf::Vector2f tam = sf::Vector2f(50.f, 50.f));
			Jogador(int indice, bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, sf::Vector2f tam);
			~Jogador();

			void executar();
			void mover(char direcao = '0');
			void colidir(Entidade* outra, std::string direcao = "");
			void colidir_ataque(Entidade* outra, std::string direcao = "");
			void ataque();
			void set_venceu(bool v) { venceu = v; };
			bool get_venceu() const  { return venceu; };

			sf::Vector2f get_ataque_posicao() { return ataque_corpo.getPosition(); }
			sf::Vector2f get_ataque_tamanho() { return ataque_corpo.getSize(); }

			const int get_dano() const { return dano_ataque; }

			void desenhar();
			void salvar(std::ofstream& arquivo);

		};
	}
}