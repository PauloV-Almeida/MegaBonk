#include "../include/GerenciadorColisoes.h"
#include <cmath>
#include <iostream>

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

	const bool GerenciadorColisoes::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const
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
				colisor(pe1, pe2, true);


			else if (std::fabs(distancia.x) - std::fabs((tam1.x + tam2.x) / 2.f) >=
				std::fabs(distancia.y) - std::fabs((tam1.y + tam2.y) / 2.f))
				colisor(pe1, pe2, false);
		}

		return colidiu;
	}
	void GerenciadorColisoes::colisor(Entidades::Entidade* pe1, Entidades::Entidade* pe2, bool vertical)const
	{
		sf::Vector2f pos1 = pe1->get_posicao();
		sf::Vector2f pos2 = pe2->get_posicao();
		sf::Vector2f tam1 = pe1->get_tamanho();
		sf::Vector2f tam2 = pe2->get_tamanho();
		if (vertical)
		{
			if (pos1.y < pos2.y)
			{
				sf::Vector2f aux(pos1.x, pos2.y - (tam2.y + tam1.y) / 2.f);
				pe1->set_posicao(aux);

			}
			else
			{
				sf::Vector2f aux(pos1.x, pos2.y + (tam2.y + tam1.y) / 2.f);
				pe1->set_posicao(aux);

			}
		}
		else
		{
			if (pos1.x < pos2.x)
			{
				sf::Vector2f aux(pos2.x - (tam2.x + tam1.x) / 2.f, pos1.y);
				pe1->set_posicao(aux);

			}
			else
			{
				sf::Vector2f aux(pos2.x + (tam2.x + tam1.x) / 2.f, pos1.y);
				pe1->set_posicao(aux);

			}
		}
	}

	void GerenciadorColisoes::tratarColisoesJogsObstacs()
	{
		if (!LJogs) {
			std::cout << "[Colisao] LJogs == nullptr\n";
			return;
		}
		if (LOs.empty()) {
			std::cout << "[Colisao] LOs está vazio\n";
			return;
		}

		// debug: conta jogadores
		int cntJ = 0;
		auto itrCount = LJogs->get_Primeiro();
		while (itrCount != NULL) { cntJ++; itrCount++; }
		std::cout << "[Colisao] jogadores na lista: " << cntJ << ", obstaculos: " << LOs.size() << "\n";

		auto itr = LJogs->get_Primeiro();
		while (itr != NULL)
		{
			Entidades::Entidade* e = *itr;
			Entidades::Personagens::Jogador* jog =
				dynamic_cast<Entidades::Personagens::Jogador*>(e);

			if (jog)
			{
				// para cada obstáculo
				for (auto obs : LOs)
				{
					if (!obs || !obs->get_vivo()) continue;

					sf::Vector2f posJ = jog->get_posicao();
					sf::Vector2f posO = obs->get_posicao();
					sf::Vector2f tamJ = jog->get_tamanho();
					sf::Vector2f tamO = obs->get_tamanho();
					sf::Vector2f dist = posJ - posO;

					float ax = std::fabs(dist.x);
					float ay = std::fabs(dist.y);
					float halfX = std::fabs((tamJ.x + tamO.x) / 2.f);
					float halfY = std::fabs((tamJ.y + tamO.y) / 2.f);

					// debug de tamanhos e posições
					std::cout << "[Colisao] Jog pos(" << posJ.x << "," << posJ.y << ") tam(" << tamJ.x << "," << tamJ.y << ")"
						<< " Obs pos(" << posO.x << "," << posO.y << ") tam(" << tamO.x << "," << tamO.y << ")\n";

					// se não há sobreposição, pular
					if (!(ax <= halfX && ay <= halfY)) {
						//std::cout << "[Colisao] sem sobreposicao\n";
						continue;
					}

					bool colisaoVertical = (ax - halfX) <= (ay - halfY);

					// se colidiu, colisor já ajusta posição
					if (verificarColisao(jog, obs))
					{
						std::cout << "[Colisao] DETECTADA entre jogador e obstaculo, vertical=" << colisaoVertical << "\n";
						sf::Vector2f vel = jog->get_vel();
						if (colisaoVertical)
						{
							vel.y = 0.f;
						}
						else
						{
							vel.x = 0.f;
						}
						jog->set_vel(vel);
					}
				}
			}

			itr++;
		}
	}

	void GerenciadorColisoes::tratarColisoesJogsInimigs()
	{
		if (!LJogs) {
			std::cout << "[Colisao] LJogs == nullptr (inimigos)\n";
			return;
		}
		if (LIs.empty()) {
			//std::cout << "[Colisao] LIs está vazio\n";
			return;
		}

		auto itr = LJogs->get_Primeiro();
		while (itr != NULL)
		{
			Entidades::Entidade* e = *itr;
			Entidades::Personagens::Jogador* jog =
				dynamic_cast<Entidades::Personagens::Jogador*>(e);

			if (jog)
			{
				for (auto ini : LIs)
				{
					if (!ini) continue;

					sf::Vector2f posJ = jog->get_posicao();
					sf::Vector2f posI = ini->get_posicao();
					sf::Vector2f tamJ = jog->get_tamanho();
					sf::Vector2f tamI = ini->get_tamanho();
					sf::Vector2f dist = posJ - posI;

					float ax = std::fabs(dist.x);
					float ay = std::fabs(dist.y);
					float halfX = std::fabs((tamJ.x + tamI.x) / 2.f);
					float halfY = std::fabs((tamJ.y + tamI.y) / 2.f);

					if (!(ax <= halfX && ay <= halfY)) continue;

					bool colisaoVertical = (ax - halfX) <= (ay - halfY);

					if (verificarColisao(jog, ini))
					{
						sf::Vector2f vel = jog->get_vel();
						if (colisaoVertical)
							vel.y = 0.f;
						else
							vel.x = 0.f;
						jog->set_vel(vel);
					}
				}
			}

			itr++;
		}
	}
		
	void GerenciadorColisoes::executar()
	{
		
		tratarColisoesJogsObstacs();
		tratarColisoesJogsInimigs();
	}

}