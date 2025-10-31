#pragma once

#include "../MegaBonk/stdafx/stdafx.h"

class Personagem
{
protected:
	sf::RectangleShape corpo;
	sf::Vector2f velocidade;
public:
	Personagem(const sf::Vector2f pos, const sf::Vector2f vel, const sf::Vector2f tam);
	Personagem();
	~Personagem();
	const sf::RectangleShape getCorpo();
	void setColor(sf::Color cor);
	virtual void move();
};
