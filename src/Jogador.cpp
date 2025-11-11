#include "../include/Jogador.h"

namespace Entidades
{
	namespace Personagens
	{
		Jogador::Jogador(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f tam) :Personagem(pos, vel, tam)
		{
			setColor(sf::Color::Blue);
		}

		Jogador::Jogador()
		{
			setColor(sf::Color::Blue);
		}

		Jogador::~Jogador()
		{
		}

		void Jogador::mover()
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				corpo.move(-velocidade.x, velocidade.y);

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				corpo.move(velocidade.x, velocidade.y);

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				corpo.move(-velocidade.x, -velocidade.y);

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				corpo.move(velocidade.x, -velocidade.y);

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				corpo.move(-velocidade.x, 0.0f);

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				corpo.move(velocidade.x, 0.0f);

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				corpo.move(0.0f, -velocidade.y);

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				corpo.move(0.0f, velocidade.y);
		}
	}
}