#pragma once

#include "Inimigo.h"
#include "Jogador.h"
#define COOLDOWN_ATQ_ARVORE 2.0f
#define DANO_PROJETIL_ARVORE 20

namespace Entidades
{
	namespace Personagens
	{
		class ArvoreMonstro : public Inimigo
		{
		private:
			float tempovinha;
			float cooldownatq = COOLDOWN_ATQ_ARVORE;
			int danoprojetil = DANO_PROJETIL_ARVORE;
		public:
			ArvoreMonstro(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Vector2f vel = sf::Vector2f(50.f, 50.f), sf::Vector2f tam = sf::Vector2f(0.f, 0.f));
			ArvoreMonstro(bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, float dmg, sf::Vector2f tam, float emp);
			~ArvoreMonstro();

			void projetar();
			void desenhar();
			void executar();
			void danificar();
			void colidir(Jogador* pJog, std::string direcao = "");
		};
	}
}

