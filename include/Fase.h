#pragma once

#include <SFML/Graphics.hpp>

#include "Entidades.h"
#include "Jogador.h"
#include "ListaEntidades.h"
#include "GerenciadorGrafico.h"
#include "GerenciadorColisoes.h"
#include "GerenciadorEventos.h"
#include "GerenciadorEstado.h"
#include "Estado.h"



#include <fstream>
#include <string>
#include <iostream>

namespace Fases
{
	class Fase : public Ente, public Estados::Estado
	{
	protected:
		Listas::ListaEntidades jogadores;
		Listas::ListaEntidades inimigos;
		Listas::ListaEntidades obstaculos;


		Gerenciadores::GerenciadorColisoes gColisoes;
		Gerenciadores::GerenciadorEventos* pGE;

		sf::RectangleShape corpo;
	protected:
		Entidades::Entidade* criarEsqueleto(std::ifstream& arquivo);
		Entidades::Entidade* criarPlataformas(std::ifstream& arquivo);
		

		virtual void criarInimigos(Entidades::Entidade* ini) = 0;
		virtual void criarObstaculos(Entidades::Entidade* obs) = 0;
		void criarCenario(std::string arquivo);

	public:
		Fase(int id = -1);
		virtual ~Fase();
		virtual void executar() = 0;
		void desenhar();
	};
}