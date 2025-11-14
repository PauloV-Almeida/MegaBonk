#include "../include/Personagem.h"

namespace Entidades
{
	namespace Personagens
	{
		Personagem::Personagem(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f tam)
		{
			corpo.setSize(tam); // define o tamanho primeiro
			corpo.setOrigin(tam.x / 2.f, tam.y / 2.f); // agora a origem centraliza corretamente
			corpo.setPosition(pos);
			velocidade = vel;
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

		sf::RectangleShape Personagem::getCorpo()
		{
			return corpo;
		}

		void Personagem::mover()
		{
		}
	}
}