#pragma once

#include "Fase.h"

#define TEMPOFIM 1000

#define ARQUIVO_CENARIO_1 "./salvar/fase1/cenario.dat"
#define SALVAR_CENARIO_1 "./salvar/fase1/seed.dat"

namespace Fases
{
	class Deserto : public Fase
	{
	private:
		int fim;

	public:
		Deserto(int n_jogadores);
		Deserto();
		~Deserto();

		void executar();
		void salvar();
		void carregar();
		void resetar();

	};
}
