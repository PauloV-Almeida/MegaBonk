#pragma once

#include <SFML/Graphics.hpp>
#include "../stdafx/stdafx.h"
#include "Personagem.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "ListaEntidades.h"
#include "Plataforma.h"


namespace Gerenciadores
{
	class GerenciadorColisoes
	{
	private:
		std::vector<Entidades::Personagens::Inimigo*> LIs;
		std::list<Entidades::Obstaculos::Obstaculo*> LOs;
		//std::set <Entidades::Projetil*> LPs;

		Listas::ListaEntidades* LJogs;

		static GerenciadorColisoes* instance;

	private:
		const bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2, std::string* direcao1 = nullptr, std::string* direcao2 = nullptr)const;
		void colisor();
		void tratarColisoesJogsObstacs(Entidades::Personagens::Jogador* pJog, Entidades::Obstaculos::Obstaculo* pObs, std::string* dir1 = nullptr, std::string* dir2 = nullptr)const;
		void tratarColisoesJogsInimigs(Entidades::Personagens::Jogador* pJog, Entidades::Personagens::Inimigo* pIni, std::string* dir1 = nullptr, std::string* dir2 = nullptr)const;
		void tratarColisoesInimigsObstacs(Entidades::Personagens::Inimigo* pIni, Entidades::Obstaculos::Obstaculo* pObs, std::string* dir1 = nullptr, std::string* dir2 = nullptr)const;
		//void tratarColisoesJogsProjeteis();

		void verificarAtaqueJogadorInimigo(Entidades::Personagens::Jogador* pJog, Entidades::Personagens::Inimigo* pIni);

		
		
	public:
		GerenciadorColisoes();
		~GerenciadorColisoes();
		static GerenciadorColisoes* get_instance();
		void incluirJogadores(Listas::ListaEntidades* ListaJg) {if(ListaJg){ LJogs = ListaJg;}}
		Listas::ListaEntidades* get_ListaJogadores() { return LJogs; }
		void incluirInimigos(Listas::ListaEntidades* ListaIni) {
			if (!ListaIni) return;

			// percorre todos os elementos
			auto itr = ListaIni->get_Primeiro();

			while (itr != NULL)
			{
				Entidades::Entidade* e = *itr;

				// tenta converter para inimigo
				Entidades::Personagens::Inimigo* ini =
					dynamic_cast<Entidades::Personagens::Inimigo*>(e);

				if (ini)
				{
					LIs.push_back(ini);
				}

				itr++; // avança
			}
		}
		void incluirObstaculos(Listas::ListaEntidades* ListaObs) {
			if (!ListaObs) return;
			// percorre todos os elementos
			auto itr = ListaObs->get_Primeiro();
			while (itr != NULL)
			{
				Entidades::Entidade* e = *itr;
				// tenta converter para obstaculo
				Entidades::Obstaculos::Obstaculo* obs =
					dynamic_cast<Entidades::Obstaculos::Obstaculo*>(e);
				if (obs)
				{
					LOs.push_back(obs);
				}
				itr++; // avança
			}
		}
		//void incluirProjetil(Projetil* p);

		void executar();
	};
}