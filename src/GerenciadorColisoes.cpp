#include "../include/GerenciadorColisoes.h"

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
		pJog()
	{

	}

	GerenciadorColisoes::~GerenciadorColisoes()
	{

	}

	const bool GerenciadorColisoes::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const
	{
		sf::Vector2f pos1 = pe1->get_posicao();
		sf::Vector2f pos2 = pe2->get_posicao();
		sf::Vector2f tam1 = pe1->get_tamanho();
		sf::Vector2f tam2 = pe2->get_tamanho();
		sf::Vector2f distancia = pos1 - pos2;
		sf::Vector2f aux;

		if (fabs(distancia.x) <= fabs((tam1.x + tam2.x) / 2) && fabs(distancia.y) <= fabs((tam1.y + tam2.y) / 2.0))
		{
			if (fabs(distancia.x) - fabs((tam1.x + tam2.x) / 2) < fabs(distancia.y) - fabs((tam1.y + tam2.y) / 2.0))
			{
				if (pos1.y < pos2.y)
				{
					aux = (pos1.x, pos2.y - (tam2.y + tam1.y) / 2.f);
					pe1->set_posicao(aux);
					pe1->colidir(pe2, "Embaixo");
					pe2->colidir(pe1, "Emcima");
				}
				else
				{
					aux = (pos1.x, pos2.y + (tam2.y + tam1.y) / 2.f);
						pe1->set_posicao(aux);
					pe1->colidir(pe2, "Emcima");
					pe2->colidir(pe1, "Embaixo");
				}
			}
			else if (fabs(distancia.x) - fabs((tam1.x + tam2.x) / 2) > fabs(distancia.y) - fabs((tam1.y + tam2.y) / 2.0))
			{
				if (pos1.x < pos2.x)
				{
					aux = (pos2.x - (tam2.x + tam1.x) / 2.f, pos1.y);
					pe1->set_posicao(aux);
					pe1->colidir(pe2, "Direita");
					pe2->colidir(pe1, "Esquerda");
				}
				else
				{
					aux = (pos2.x + (tam2.x + tam1.x) / 2.f, pos1.y);
					pe1->set_posicao(aux);
					pe1->colidir(pe2, "Esquerda");
					pe2->colidir(pe1, "Direita");
				}

			}
		}
	}

	/*void GerenciadorColisoes::tratarColisoesJogsObstacs()
	{
		std::list<Obstaculo*>::iterator it;

		if (!LOs.empty())
		{
			if (pJog1)
				for (it = LOs.begin(); it != LOs.end(); ++it)
					verificarColisao(static_caspJog1, *it);
			if (pJog2)
				for (it = LOs.begin(); it != LOs.end(); ++it)
					verificarColisao(pJog2, *it);
		}
	}*/

	void GerenciadorColisoes::tratarColisoesJogsInimigs()
	{
		if (!LIs.empty())
		{
			int i;
			if (!pJog1)
				for (i = 0; i < LIs.size(); i++)
					verificarColisao(pJog1, LIs[i]);

			if (pJog2)
				for (i = 0; i < LIs.size(); i++)
					verificarColisao(pJog2, LIs[i]);
		}
	}

	/*void GerenciadorColisoes::tratarColisoesJogsProjeteis()
	{
		std::list<Entidades::Projetil*>::iterator it;
		if (!LPs.empty())
		{
			if (pJog1)
				for (it = LPs.begin(); it != LPs.end(); ++it)
					verificarColisao(pJog1, *it);
			if (pJog2)
				for (it = LPs.begin(); it != LPs.end(); ++it)
					verificarColisao(pJog2, *it);
		}
	}*/

	void GerenciadorColisoes::setJogadores(Entidades::Personagens::Jogador* j)
	{
		if (!pJog1)
			pJog1 = j;
		else
			pJog2 = j;
	}
	void GerenciadorColisoes::incluirInimigo(Entidades::Personagens::Inimigo* i) { LIs.push_back(i); }
	//void GerenciadorColisoes::incluirObstaculo(Entidades::Obstaculos::Obstaculo* o) { LOs.push_back(o); }
	//void GerenciadorColisoes::incluirProjetil(Entidades::Projetil* p) { LPs.insert(p); }
	void GerenciadorColisoes::executar()
	{
		tratarColisoesJogsInimigs();
		tratarColisoesJogsObstacs();
		tratarColisoesJogsProjeteis();
	}

}