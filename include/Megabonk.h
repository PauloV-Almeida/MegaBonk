#pragma once  

#include "GerenciadorGrafico.h"  
//#include "GerenciadorEventos.h"  
//#include "Coliseu.h"  
//#include "Masmorra.h"  
//#include "Jogador.h"  
//#include "Menu.h"

class MegaBonk
{
private:
	Gerenciadores::GerenciadorGrafico* pGG;


	// Jogadores como atributos  
	//Entidades::Personagens::Jogador p1;
	//Entidades::Personagens::Jogador p2;

	//Fases::Coliseu coliseu;
	//Fases::Masmorra masmorra;

	//Menu menu;

	//Fases::Fase* faseAtual;

public:
	MegaBonk();
	~MegaBonk();

	void executar();
};