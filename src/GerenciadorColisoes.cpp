#include "../include/GerenciadorColisoes.h"
#include <cmath>
#include <iostream>
#include <algorithm>

namespace Gerenciadores
{
	GerenciadorColisoes::GerenciadorColisoes() :
		LIs(), LOs(), LJogs(nullptr)
	{
		LIs.clear();
		LOs.clear();
	}
	GerenciadorColisoes::~GerenciadorColisoes()
	{
		LIs.clear();
		LOs.clear();
	}

	// mantém sua implementação existente de verificarColisao...
	const bool GerenciadorColisoes::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2, std::string* direcao1, std::string* direcao2) const
	{
		if (!pe1 || !pe2) return false;

		bool colidiu = false;

		sf::Vector2f pos1 = pe1->get_posicao();
		sf::Vector2f pos2 = pe2->get_posicao();
		sf::Vector2f tam1 = pe1->get_tamanho();
		sf::Vector2f tam2 = pe2->get_tamanho();
		sf::Vector2f distancia = pos1 - pos2;

		if (std::fabs(distancia.x) <= std::fabs((tam1.x + tam2.x) / 2.f) &&
			std::fabs(distancia.y) <= std::fabs((tam1.y + tam2.y) / 2.f))
		{
			colidiu = true;

			if (std::fabs(distancia.x) - std::fabs((tam1.x + tam2.x) / 2.f) <=
				std::fabs(distancia.y) - std::fabs((tam1.y + tam2.y) / 2.f))
			{
				if (pos1.y < pos2.y)
				{
					sf::Vector2f aux(pos1.x, pos2.y - (tam2.y + tam1.y) / 2.f);
					pe1->set_posicao(aux);
					// corrigido: usar strings esperadas por Jogador::colidir
					if (direcao1) *direcao1 = "Abaixo";
					if (direcao2) *direcao2 = "Acima";
				}
				else
				{
					sf::Vector2f aux(pos1.x, pos2.y + (tam2.y + tam1.y) / 2.f);
					pe1->set_posicao(aux);
					if (direcao1) *direcao1 = "Acima";
					if (direcao2) *direcao2 = "Abaixo";
				}
			}
			else if (std::fabs(distancia.x) - std::fabs((tam1.x + tam2.x) / 2.f) >=
				std::fabs(distancia.y) - std::fabs((tam1.y + tam2.y) / 2.f))
			{
				if (pos1.x < pos2.x)
				{
					sf::Vector2f aux(pos2.x - (tam2.x + tam1.x) / 2.f, pos1.y);
					pe1->set_posicao(aux);
					if (direcao1) *direcao1 = "Direita";
					if (direcao2) *direcao2 = "Esquerda";
				}
				else
				{
					sf::Vector2f aux(pos2.x + (tam2.x + tam1.x) / 2.f, pos1.y);
					pe1->set_posicao(aux);
					if (direcao1) *direcao1 = "Esquerda";
					if (direcao2) *direcao2 = "Direita";
				}
			}
		}

		return colidiu;
	}

	// implementação original de incluirInimigos / incluirObstaculos (mantidas)
	void GerenciadorColisoes::incluirInimigos(Listas::ListaEntidades* ListaIni) {
		auto itr = ListaIni->get_Primeiro();
		while (itr != nullptr)
		{
			Entidades::Entidade* e = *itr;
			Entidades::Personagens::Inimigo* ini = dynamic_cast<Entidades::Personagens::Inimigo*>(e);
			if (ini && ini->get_vivo())
			{
				// evita duplicar
				if (std::find(LIs.begin(), LIs.end(), ini) == LIs.end())
					LIs.push_back(ini);
			}
			itr++;
		}
	}
	void GerenciadorColisoes::incluirObstaculos(Listas::ListaEntidades* ListaObs) {
		auto itr = ListaObs->get_Primeiro();
		while (itr != nullptr)
		{
			Entidades::Entidade* e = *itr;
			Entidades::Obstaculos::Obstaculo* obs = dynamic_cast<Entidades::Obstaculos::Obstaculo*>(e);
			if (obs && obs->get_vivo())
			{
				// evita duplicar
				if (std::find(LOs.begin(), LOs.end(), obs) == LOs.end())
					LOs.push_back(obs);
			}
			itr++;
		}
	}

	// métodos para Fase chamar diretamente quando criar/remover entidades:
	void GerenciadorColisoes::adicionarInimigo(Entidades::Personagens::Inimigo* ini)
	{
		if (!ini) return;
		if (std::find(LIs.begin(), LIs.end(), ini) == LIs.end())
			LIs.push_back(ini);
	}
	void GerenciadorColisoes::removerInimigo(Entidades::Personagens::Inimigo* ini)
	{
		if (!ini) return;
		auto it = std::find(LIs.begin(), LIs.end(), ini);
		if (it != LIs.end()) {
			std::cerr << "[GerenciadorColisoes] removerInimigo ptr=" << *it << " no frame\n";
			LIs.erase(it);
		}
	}
	void GerenciadorColisoes::limparInimigos()
	{
		LIs.clear();
	}

	void GerenciadorColisoes::adicionarObstaculo(Entidades::Obstaculos::Obstaculo* obs)
	{
		if (!obs) return;
		if (std::find(LOs.begin(), LOs.end(), obs) == LOs.end())
			LOs.push_back(obs);
	}
	void GerenciadorColisoes::removerObstaculo(Entidades::Obstaculos::Obstaculo* obs)
	{
		if (!obs) return;
		auto it = std::find(LOs.begin(), LOs.end(), obs);
		if (it != LOs.end()) LOs.erase(it);
	}
	void GerenciadorColisoes::limparObstaculos()
	{
		LOs.clear();
	}

	// resto do colisor — adapte para usar LIs e LOs (mantive sua lógica original)
	void GerenciadorColisoes::colisor()
	{
		std::string dir1, dir2;

		int cntJ = 0;
		if (LJogs)
		{
			auto itrCount = LJogs->get_Primeiro();
			while (itrCount != nullptr)
			{
				cntJ++; itrCount++;
			}
		}

		auto itr = (LJogs ? LJogs->get_Primeiro() : Listas::Lista<Entidades::Entidade>::Iterator<Entidades::Entidade>(nullptr));
		while (itr != nullptr)
		{
			Entidades::Entidade* e = *itr;
			Entidades::Personagens::Jogador* jog =
				dynamic_cast<Entidades::Personagens::Jogador*>(e);

			for (auto it = LOs.begin(); it != LOs.end(); ++it)
			{
				if (!jog || !(*it)) continue;
				if (verificarColisao(jog, *it, &dir1, &dir2))
					tratarColisoesJogsObstacs(jog, *it, &dir1);
			}

			for (auto itI = LIs.begin(); itI != LIs.end(); ++itI)
			{
				Entidades::Personagens::Inimigo* ini = *itI;
				if (!ini || !ini->get_vivo()) continue;

				if (verificarColisao(jog, ini, &dir1, &dir2))
				{
					tratarColisoesJogsInimigs(jog, ini, &dir1, &dir2);
				}
			}

			for (auto itI = LIs.begin(); itI != LIs.end(); ++itI)
			{
				Entidades::Personagens::Inimigo* ini = *itI;
				if (!ini || !ini->get_vivo()) continue;

				for (auto itO = LOs.begin(); itO != LOs.end(); ++itO)
				{
					Entidades::Obstaculos::Obstaculo* obs = *itO;
					if (!obs || !obs->get_vivo()) continue;

					if (verificarColisao(ini, obs, &dir1, &dir2))
					{
						sf::Vector2f vel = ini->get_vel();
						if (dir1 == "Emcima" || dir1 == "Embaixo")
							vel.y = 0.f;
						else
							vel.x = 0.f;
						ini->set_vel(vel);

					}
				}
			}

			itr++;
		}

	}

	void GerenciadorColisoes::colidir_ataque(Entidades::Personagens::Jogador* ataque, std::string direcao)
	{
		if (!ataque) return;

		sf::Vector2f posAtq = ataque->get_ataque_posicao();
		sf::Vector2f tamAtq = ataque->get_ataque_tamanho();

		for (auto ini : LIs)
		{
			if (!ini || !ini->get_vivo()) continue;

			sf::Vector2f posIni = ini->get_posicao();
			sf::Vector2f tamIni = ini->get_tamanho();

			sf::Vector2f distancia = posAtq - posIni;

			if (std::fabs(distancia.x) <= std::fabs((tamAtq.x + tamIni.x) / 2.f) &&
				std::fabs(distancia.y) <= std::fabs((tamAtq.y + tamIni.y) / 2.f))
			{
				ataque->colidir_ataque(static_cast<Entidades::Entidade*>(ini), direcao);
				break;
			}
		}
	}

	void GerenciadorColisoes::tratarColisoesJogsObstacs(Entidades::Personagens::Jogador* pJog, Entidades::Obstaculos::Obstaculo* pObs, std::string* dir1)const
	{
		if (!pJog || !pObs || !dir1) return;

		// Se colisão vertical com superfície por cima do obstáculo (jogador pousou)
		if (*dir1 == "Abaixo")
		{
			// zera velocidade vertical e marca noChao para evitar reaplicar gravidade
			sf::Vector2f v = pJog->get_vel();
			v.y = 0.f;
			pJog->set_vel(v);

			// usa o novo setter adicionado em Personagem
			pJog->set_noChao(true);
		}

		// chama o comportamento específico das entidades
		pJog->colidir(pObs, *dir1);
		pObs->obstaculizar(pJog);
	}

	void GerenciadorColisoes::tratarColisoesJogsInimigs(Entidades::Personagens::Jogador* pJog, Entidades::Personagens::Inimigo* pIni, std::string* dir1, std::string* dir2)const
	{
		pJog->colidir(pIni, *dir1);
		pIni->danificar(pJog, *dir2);
	}


	void GerenciadorColisoes::executar()
	{
		colisor();
	}

}