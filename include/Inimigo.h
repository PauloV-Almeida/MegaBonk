#pragma once

#define RAIOX 200.0f
#define RAIOY 200.0f

#include "Personagem.h"
#include "Jogador.h"
namespace Entidades
{
	namespace Personagens
	{
		class Inimigo :public Personagem
		{
		private:
			Jogador* j;
			int nivel_maldade;
		public:
			Inimigo(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f tam);
			Inimigo();
			~Inimigo();
			void setJogado(Jogador* jog);
			void mover();
			void movimentoaleatorio();
			void persegue(sf::Vector2f posJogador, sf::Vector2f posInimigo);
			void salvarDataBuffer() {};
			virtual void executar() = 0;
			virtual void danificar(Jogador* p) = 0;
			virtual void salva() {};

		};
	}
}
