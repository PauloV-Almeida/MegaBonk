#pragma once

#include <SFML/Graphics.hpp>
#include "../stdafx/stdafx.h"
#include "Personagem.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "ListaEntidades.h"
#include "Plataforma.h"
#include "Projetil.h"
#include <vector>
#include <list>
#include <algorithm>

namespace Gerenciadores
{
	class GerenciadorColisoes
	{
	private:
		std::vector<Entidades::Personagens::Inimigo*> LIs;
		std::list<Entidades::Obstaculos::Obstaculo*> LOs;
		//std::set <Entidades::Projetil*> LPs;

		Listas::ListaEntidades* LJogs;


	private:
		const bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2, std::string* direcao1 = nullptr, std::string* direcao2 = nullptr)const;
		void colisor();
		void tratarColisoesJogsObstacs(Entidades::Personagens::Jogador* pJog, Entidades::Obstaculos::Obstaculo* pObs, std::string* dir1 = nullptr)const;
		void tratarColisoesJogsInimigs(Entidades::Personagens::Jogador* pJog, Entidades::Personagens::Inimigo* pIni, std::string* dir1 = nullptr, std::string* dir2 = nullptr)const;

		//void tratarColisoesJogsProjeteis();

	public:
		GerenciadorColisoes();
		~GerenciadorColisoes();
		void incluirJogadores(Listas::ListaEntidades* ListaJg) { if (ListaJg) { LJogs = ListaJg; } }
		void incluirInimigos(Listas::ListaEntidades* ListaIni);
		void incluirObstaculos(Listas::ListaEntidades* ListaObs);
		// métodos para Fase atualizar explicitamente as coleções internas:
		void adicionarInimigo(Entidades::Personagens::Inimigo* ini);
		void removerInimigo(Entidades::Personagens::Inimigo* ini);
		void limparInimigos();

		void adicionarObstaculo(Entidades::Obstaculos::Obstaculo* obs);
		void removerObstaculo(Entidades::Obstaculos::Obstaculo* obs);
		void limparObstaculos();

		//void incluirProjetil(Listas::ListaEntidades* ListaProj);
		void colidir_ataque(Entidades::Personagens::Jogador* ataque, std::string direcao);

		void executar();
	};
}