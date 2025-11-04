#pragma once

#include "../MegaBonk/stdafx/stdafx.h"
#include "../MegaBonk/GerenciadorGrafico.h"

#define GRAVIDADE 0.3
#define VELOCIDADE 0.1
#define VEL_MAX 10.0

class Ente
{
protected:
	int id;
	static Gerenciadores::GerenciadorGrafico* pGG;
	sf::Texture* texture;
public:
    Ent();
    virtual ~Ent();

    virtual void desenho() = 0;

    virtual void executar() = 0;
};