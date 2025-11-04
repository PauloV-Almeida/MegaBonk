#include "../include/Megabonk.h"

MegaBonk::MegaBonk():
	pGG(Gerenciadores::GerenciadorGrafico::get_instance())
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
		
		pGG->mostrar();
	}
}