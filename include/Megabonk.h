#pragma once  

#include <SFML/Graphics.hpp>

#include "GerenciadorGrafico.h"  
//#include "GerenciadorEventos.h"  
#include "Deserto.h"  
//#include "Masmorra.h"  
#include "Jogador.h"  
//#include "Menu.h"

class MegaBonk
{
private:
	Gerenciadores::GerenciadorGrafico* pGG;
	
	
public:
	MegaBonk();
	~MegaBonk();

	void executar();
};