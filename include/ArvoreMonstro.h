#pragma once

#include "Inimigo.h"
#include "Projetil.h"



namespace Entidades
{
	namespace Personagens
	{
		class ArvoreMonstro : public Inimigo
		{
		private:
			Projetil* pProjetil;
			float delay_ataque;
		public:
			ArvoreMonstro(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Vector2f vel = sf::Vector2f(50.f, 50.f), sf::Vector2f tam = sf::Vector2f(0.f, 0.f));
			ArvoreMonstro(bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, float dmg, sf::Vector2f tam, int delay_ataque);
			~ArvoreMonstro();

			
			void desenhar();
			void mover();
			void atacar();
			void executar();
			void colidir(Entidade* outra, std::string direcao = "");
			void colidirAtaque();
		};
	}
}

