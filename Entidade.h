#pragma once

#include "../MegaBonk/Ente.h"

namespace Entidades
{
	class Entidade
	{
	protected:
		int x;
		int y;
		
	public:
		Entidade();
		~Entidade();
		
		virtual void executar();
		salvar();

	protected:
		void salvarDataBuffer()
	};
}