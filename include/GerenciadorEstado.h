#pragma once

#include "Estado.h"
#include <stdexcept>
#include <vector>
/*Estado:
0: Menu principal;
1: Fase 1 com 1 jogador;
2: Fase 2 com 1 jogador;
3: GameOver;
4: Ranking;
5: Fase 2 com 2 jogador;
6: Fase 1 com 2 jogador;
7: Fim;
*/

namespace Gerenciadores
{
	class Gerenciador_Estado
	{
	private:
		int AtualEstado;
		std::vector<Estados::Estado*> vector_estados;
		static Gerenciador_Estado* instance;
		Gerenciador_Estado();
	public:
		~Gerenciador_Estado();

		static Gerenciador_Estado* get_instance();
		void set_AtualEstado(int i);
		int get_AtualEstadoID();
		void add_estado(Estados::Estado* pEstado);
		void reseta_AtualEstado();
		void executar();

	};
}