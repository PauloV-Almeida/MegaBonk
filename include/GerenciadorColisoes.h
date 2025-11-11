#pragma once

#include <SFML/Graphics.hpp>
#include "../stdafx/stdafx.h"
#include "Personagem.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "ListaEntidades.h"


namespace Gerenciadores
{
	class GerenciadorColisoes
	{
	private:
		std::vector<Entidades::Personagens::Inimigo*> LIs;
		//std::list<Entidades::Obstaculos::Obstaculo*> LOs;
		//std::set <Entidades::Projetil*> LPs;

		Entidades::Personagens::Jogador* pJog;


	private:
		const bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2)const;
		void tratarColisoesJogsObstacs();
		void tratarColisoesJogsInimigs();
		void tratarColisoesJogsProjeteis();

		static GerenciadorColisoes* instance;
		GerenciadorColisoes();
	public:

		~GerenciadorColisoes();
		static GerenciadorColisoes* get_instance();
		void setJogadores(Entidades::Personagens::Jogador* j);
		void incluirInimigo(Entidades::Personagens::Inimigo* i);
		//void incluirObstaculo(Obstaculo* o);
		//void incluirProjetil(Projetil* p);

		void executar();
	};
}