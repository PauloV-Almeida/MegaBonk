#include "../include/Personagem.h"

namespace Entidades
{
	namespace Personagens
	{
		Personagem::Personagem(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f tam)
		{
			corpo.setPosition(pos);
			velocidade = vel;
			corpo.setSize(tam);
		}
		Personagem::Personagem()
		{

		}

		Personagem::~Personagem()
		{
		}

		void Personagem::setColor(sf::Color cor)
		{
			corpo.setFillColor(cor);
		}

		const sf::RectangleShape Personagem::getCorpo()
		{
			return corpo;
		}

		void Personagem::mover()
		{
		}
	}
}