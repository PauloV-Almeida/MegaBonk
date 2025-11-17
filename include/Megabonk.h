#pragma once  

#include <SFML/Graphics.hpp>

#include "Deserto.h"
#include "GerenciadorGrafico.h"
#include "GerenciadorEventos.h"
#include "GerenciadorEstado.h"
#include "MainMenu.h"


class MegaBonk
{
private:
	Gerenciadores::GerenciadorGrafico* pGG;
	Gerenciadores::GerenciadorEventos* pGE;
	Gerenciadores::GerenciadorEstado* pGEst;
	Menus::MainMenu main_menu;
public:
	MegaBonk();
	~MegaBonk();

	void executar();
};