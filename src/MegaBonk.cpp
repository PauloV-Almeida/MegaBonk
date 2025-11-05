#include "../include/Megabonk.h"

MegaBonk::MegaBonk():
	pGG(Gerenciadores::GerenciadorGrafico::get_instance())
	//,pGE(Gerenciadores::GerenciadorEventos::get_instance()),
	//pGEst(Gerenciadores::GerenciadorEstados::get_instance())
{
	executar();
}

MegaBonk::~MegaBonk()
{
}

void MegaBonk::executar()
{
	while (pGG->abreJanela()) {
		pGG->limpar();
		
		//pGE->executar();
		//pGEst->executar();

		pGG->mostrar();
	}
}