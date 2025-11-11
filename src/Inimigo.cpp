#include "../include/Inimigo.h"

namespace Entidades
{
	namespace Personagens
	{
		Inimigo::Inimigo(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f tam) :Personagem(pos, vel, tam)
		{
			setColor(sf::Color::Red);
			j = NULL;
		}

		Inimigo::Inimigo() { j = NULL; };

		Inimigo::~Inimigo() {};

		void Inimigo::setJogado(Jogador* jog)
		{
			j = jog;
		}

		void Inimigo::movimentoaleatorio()
		{

		}

		void Inimigo::persegue(sf::Vector2f posJogador, sf::Vector2f posInimigo)
		{
			if ((posInimigo.x - posJogador.x) > 0)
				corpo.move(-velocidade.x, 0.0f);

			else
				corpo.move(velocidade.x, 0.0f);

			if ((posInimigo.y - posJogador.y) > 0)
				corpo.move(0.0f, -velocidade.y);

			else
				corpo.move(0.0f, velocidade.y);
		}

		void Inimigo::mover()
		{
			sf::Vector2f posJogador = j->getCorpo().getPosition();
			sf::Vector2f posInimigo = corpo.getPosition();

			if (fabs(posInimigo.x - posJogador.x) < RAIOX && fabs(posInimigo.y - posJogador.y) < RAIOY)
				persegue(posJogador, posInimigo);
			else
				movimentoaleatorio();
		}
	}
}