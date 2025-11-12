#pragma once  

#include <SFML/Graphics.hpp>

#include "GerenciadorGrafico.h"  
//#include "GerenciadorEventos.h"  
//#include "Floresta.h"  
//#include "Masmorra.h"  
//#include "Jogador.h"  
//#include "Menu.h"

class MegaBonk
{
private:
	Gerenciadores::GerenciadorGrafico* pGG;
	//Gerenciadores::GerenciadorEventos* pGE;
	//Gerenciadores::GerenciadorEstados* pGEst;
public:
	MegaBonk();
	~MegaBonk();

	void executar();
};