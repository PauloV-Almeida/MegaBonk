#pragma once

#include "Inimigo.h"
#include "Projetil.h"

#define LIMITE_PATRULHA 50.f

namespace Entidades
{
	namespace Personagens
	{
		class ArvoreMonstro : public Inimigo
		{
		private:
			Projetil* pProjetil;
			float delay_ataque;

			// Estados/parametros de movimentação do boss
			sf::Vector2f pontoEsquerda;
			sf::Vector2f pontoDireita;
			int sentido = 1; // 1 = direita, -1 = esquerda
			bool perseguindo = false;
			bool olhandoEsquerda = false;

			// Cooldowns / timers (baseados em frames / ticks simples)
			float tempoCooldownTiro = 0.f;
			bool estaAtacando = false;
			float tempoAtaque = 0.6f;
			sf::Vector2f ultimoAlvo;
		public:
			ArvoreMonstro(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Vector2f vel = sf::Vector2f(50.f, 50.f), sf::Vector2f tam = sf::Vector2f(0.f, 0.f));
			ArvoreMonstro(bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, float dmg, sf::Vector2f tam, int delay_ataque);
			~ArvoreMonstro();

			void executar();
			void desenhar();
			void mover();
			void atacar();
			void salvar(std::ofstream& arquivo);
			void colidir(Entidade* outra, std::string direcao = "");
			void colidirAtaque();
			void setProjetil(Projetil* p) { pProjetil = p; }

		};
	}
}

