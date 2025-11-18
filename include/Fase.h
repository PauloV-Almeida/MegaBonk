#pragma once

#include <SFML/Graphics.hpp>

#include "Entidades.h"
#include "Jogador.h"
#include "ListaEntidades.h"
#include "GerenciadorGrafico.h"
#include "GerenciadorColisoes.h"
#include "GerenciadorEventos.h"
#include "GerenciadorEstado.h"


#include <fstream>
#include <string>
#include <iostream>

namespace Fases
{
	class Fase : public Ente, public E
	{
	protected:
		Listas::ListaEntidades jogadores;
		Listas::ListaEntidades inimigos;

		sf::RectangleShape corpo;
	public:
		Fase(int id=-1);
		virtual ~Fase();
		virtual void executar() = 0;
		void desenhar();

		void add_jogador(Entidades::Entidade* jogador);
		//void add_inimigo(Entidades::Entidade* inimigo);

		//Entidades::Entidade* criar_Inimigos(std::ifstream& arquivo);
		void criar_scenario(std::string arquivo);
	};
}