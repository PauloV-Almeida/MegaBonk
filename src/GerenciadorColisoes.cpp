#include "../include/GerenciadorColisoes.h"
#include <cmath>

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

}
