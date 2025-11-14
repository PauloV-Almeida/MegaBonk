#include "../include/GerenciadorColisoes.h"
#include <cmath>

namespace Gerenciadores
{
	GerenciadorColisoes* GerenciadorColisoes::instance = nullptr;

	GerenciadorColisoes* GerenciadorColisoes::get_instance()
	{
		if (instance == nullptr) {
			instance = new GerenciadorColisoes();
		}
		return instance;
	}

	GerenciadorColisoes::GerenciadorColisoes() :
		LIs(),
		pJog(nullptr)
	{
	}

	GerenciadorColisoes::~GerenciadorColisoes()
	{
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
				pe1->colidir(pe2, "Embaixo");
				pe2->colidir(pe1, "Emcima");
			}
			else
			{
				sf::Vector2f aux(pos1.x, pos2.y + (tam2.y + tam1.y) / 2.f);
				pe1->set_posicao(aux);
				pe1->colidir(pe2, "Emcima");
				pe2->colidir(pe1, "Embaixo");
			}
		}
		else
		{
			if (pos1.x < pos2.x)
			{
				sf::Vector2f aux(pos2.x - (tam2.x + tam1.x) / 2.f, pos1.y);
				pe1->set_posicao(aux);
				pe1->colidir(pe2, "Direita");
				pe2->colidir(pe1, "Esquerda");
			}
			else
			{
				sf::Vector2f aux(pos2.x + (tam2.x + tam1.x) / 2.f, pos1.y);
				pe1->set_posicao(aux);
				pe1->colidir(pe2, "Esquerda");
				pe2->colidir(pe1, "Direita");
			}
		}
	}

	void GerenciadorColisoes::tratarColisoesJogsObstacs()
	{
		std::list<Entidades::Obstaculos::Obstaculo*>::iterator it;
		if (!LOs.empty())
		{
			if (pJog)
				for (it = LOs.begin(); it != LOs.end(); ++it)
					verificarColisao(pJog, *it);
			//if (pJog2) for (it = LOs.begin(); it != LOs.end(); ++it) 
				//verificarColisao(pJog2, *it); 
		}
	}


	void GerenciadorColisoes::tratarColisoesJogsInimigs()
	{
		if (!LIs.empty() && pJog)
		{
			for (size_t i = 0; i < LIs.size(); ++i)
				verificarColisao(static_cast<Entidades::Entidade*>(pJog), static_cast<Entidades::Entidade*>(LIs[i]));
		}
	}

	void GerenciadorColisoes::tratarColisoesJogsProjeteis()
	{
		// LPs está comentado no header; implementar quando disponível.
	}

	void GerenciadorColisoes::setJogadores(Entidades::Personagens::Jogador* j)
	{
		if (!pJog)
			pJog = j;
	}

	void GerenciadorColisoes::incluirInimigo(Entidades::Personagens::Inimigo* i) { LIs.push_back(i); }

	void GerenciadorColisoes::incluirObstaculo(Entidades::Obstaculos::Obstaculo* o) { LOs.push_back(o); }
	void GerenciadorColisoes::executar()
	{
		tratarColisoesJogsInimigs();
		tratarColisoesJogsObstacs();
		tratarColisoesJogsProjeteis();
	}
}