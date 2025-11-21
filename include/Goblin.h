#pragma once

#include "Inimigo.h"
#include "Jogador.h"
namespace Entidades
{
	namespace Personagens
	{
		class Goblin : public Inimigo
		{
		private:
			float furia;
		public:
			Goblin(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Vector2f vel = sf::Vector2f(50.f, 50.f), sf::Vector2f tam = sf::Vector2f(0.f, 0.f));
			Goblin(bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, float dmg, sf::Vector2f tam, float fur);
			~Goblin();


			void desenhar();
			void executar();
			void danificar();
			void colidir(Jogador* pJog, std::string direcao = "");
			void colidir(Obstaculos::Obstaculo* pObs, std::string direcao = "");
		};
	}
}
