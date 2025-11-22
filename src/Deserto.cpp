#include "../include/Deserto.h"

namespace Fases
{
	Deserto::Deserto() :
		Fase(1),
		fim(0)
	{
		corpo.setSize(sf::Vector2f(900.f, 600.f));
		texturas = pGG->carregar_texturas("./assets/Deserto.png");
		corpo.setTexture(texturas);

	}

	Deserto::Deserto(int n_jogadores) :
		Fase(6),
		fim(TEMPOFIM)
	{
		corpo.setSize(sf::Vector2f(900.f, 600.f));
		texturas = pGG->carregar_texturas("./assets/Deserto.png");
		corpo.setTexture(texturas);

	}

	Deserto::~Deserto()
	{
		if (carregado)
		{
			salvar();
		}
	}

	void Deserto::executar()
	{
		if (!carregado)
		{
			carregar();
		}

		jogadores.executar();
		obstaculos.executar();
		inimigos.executar();

		desenhar();

		if (pEG->get_AtualEstadoID() != id_estado)
		{
			Listas::Lista<Entidades::Entidade>::Iterator<Entidades::Entidade> it = inimigos.get_Primeiro();
			Entidades::Personagens::Jogador* p1 = dynamic_cast<Entidades::Personagens::Jogador*>(*it);
			it++;
			if()
		}
	}
}