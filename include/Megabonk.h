#pragma once  

#include <SFML/Graphics.hpp>

#include "GerenciadorGrafico.h"  
#include "../include/GerenciadorColisoes.h"
#include "../include/Inimigo.h"
#include "../include/Jogador.h"
#include "../include/Plataforma.h"
//#include "GerenciadorEventos.h"  
//#include "Floresta.h"  
//#include "Masmorra.h"  
//#include "Jogador.h"  
//#include "Menu.h"

class MegaBonk
{
private:
	Gerenciadores::GerenciadorGrafico* pGG;
	Gerenciadores::GerenciadorColisoes* pGC;
	Entidades::Personagens::Jogador* jogador;
	Entidades::Obstaculos::Plataforma* plataformaCentral;
	Entidades::Obstaculos::Plataforma* p1;
	Entidades::Obstaculos::Plataforma* p2;
	//Gerenciadores::GerenciadorEventos* pGE;
	//Gerenciadores::GerenciadorEstados* pGEst;
public:
	MegaBonk();
	~MegaBonk();

	void executar();
};