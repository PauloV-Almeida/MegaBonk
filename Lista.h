#pragma once

#include "../MegaBonk/stdafx/stdafx.h"

namespace Listas
{
	template <class TL>
	class Lista
	{
	private:
		template <class TE>
		class Elemento
		{
		private:
			Elemento<TE>* pProx;
			TE* pInfo;

		public:
			Elemento()
			{
				pProx = NULL;
				pInfo = NULL;
			}
			~Elemento()
			{
				pProx = NULL;
				pInfo = NULL;
			}
			void incluir(TE* p) { pInfo = p;}
			void setpProx(Elemento<TE>* pE) { pProx = pE; }
			const Elemento<TE>* getpProx() { return pProx; }

		};
		
		Elemento<TE>* pPrimeiro;
		Elemento<TE>* pUltimo;

	public:
		Lista();
		~Lista();
		void incluir(TL* p);
		void limpar();
	};

	template<class TL>
	Lista<TL>::Lista()
	{
		pPrimeiro = NULL;
		pUltimo = NULL;
	}

	template<class TL>
	Lista<TL>::~Lista()
	{
		limpar()
	}

	template<class TL>
	void Lista<TL>::incluir(TL* p)
	{
		Elemento<TL>* pNoh;
		pNoh = new Elemento<TL>();	
		pNoh->incluir(p);
		if (pPrimeiro == NULL)
		{
			pPrimeiro = pNoh;
			pUltimo = pNoh;
		}
		else
		{
			pUltimo->pProx = pNoh;
			pUltimo = pNoh;
		}
	}

	template<class TL>
	void Lista<TL>::limpar()
	{
		Elemento<TL>* aux = pPrimeiro;
		Elemento<TL>* prox;
		while (aux != NULL)
		{
			prox = aux->pProx;
			delete(aux);
			aux = prox;
		}
		pPrimeiro = NULL;
		pUltimo = NULL;
	}
	
}