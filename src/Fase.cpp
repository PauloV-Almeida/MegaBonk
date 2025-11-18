#include "../include/Fase.h"

namespace Fases
{
	Fase::Fase(int id):
		Estados::Estado(id),
		jogadores(),
		inimigos(),
		obstaculos(),
		gColisoes(),
		corpo()
	{
		gColisoes.incluirJogadores(&jogadores);
		gColisoes.incluirInimigos(&inimigos);
		gColisoes.incluirObstaculos(&obstaculos);

		pGE = Gerenciadores::GerenciadorEventos::get_instance();
	}

	Fase::~Fase()
	{
	}

	void Fase::desenhar()
	{
		pGG->desenhar(&(this)->corpo);
	}
	
	
}

