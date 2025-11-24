#pragma once

#include "Personagem.h"
#include "Jogador.h"
#include "../stdafx/stdafx.h"


namespace Entidades
{
	namespace Personagens
	{

		class Inimigo :public Personagem
		{
		protected:
			int nivel_maldade;
		public:
			Inimigo(int indice = -1,sf::Vector2f pos = sf::Vector2f(10.f, 0.f), sf::Vector2f vel = sf::Vector2f(0.f, 0.f), sf::Vector2f tam = sf::Vector2f(50.f, 50.f));
			~Inimigo();
			virtual void executar();
			virtual int get_nivMaldade() const { return nivel_maldade; }
			virtual void danificar(Entidade* outra, std::string direcao = "") = 0;
			void mover();
			virtual void salvar(std::ofstream& arquivo) = 0;
			
			
		};
	}
}