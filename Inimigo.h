#pragma once

#define RAIOX 200.0f
#define RAIOY 200.0f

#include "../MegaBonk/Personagem.h"
#include "../MegaBonk/Jogador.h"
	

class Inimigo :public Personagem
{
private:
	Jogador* j;
public:
	Inimigo(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f tam);
	Inimigo();
	~Inimigo();
	void setJogado(Jogador* jog);
	void move();
	void movimentoaleatorio();
	void persegue(sf::Vector2f posJogador, sf::Vector2f posInimigo);
};
