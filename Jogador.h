#pragma once

#include "../MegaBonk/Personagem.h"

class Jogador:public Personagem
{
private:
public:
	Jogador(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f tam);
	Jogador();
	~Jogador();
	void move();
};
