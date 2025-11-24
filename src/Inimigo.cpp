#include "../include/Inimigo.h"

namespace Entidades
{
	namespace Personagens
	{
		Inimigo::Inimigo(int indice, sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f tam) :
			Personagem(indice, pos, vel, tam)
		{
			dano = 0;
		}
		Inimigo::~Inimigo()
		{
		}

		void Inimigo::movimentoaleatorio()
		{
			static int jumpCooldown = 0;
			if (jumpCooldown > 0) --jumpCooldown;

			if (!noChao)
				vel.y += GRAVIDADE;

			int r = std::rand() % 1000;
			if (r < 6 && noChao && jumpCooldown == 0)
			{
				vel.y = -6.0f;
				noChao = false;
				jumpCooldown = 120;
			}

			float muda = ((static_cast<float>(std::rand() % 101) / 100.f) - 0.5f) * 0.4f;
			vel.x += muda;


			vel.x *= 0.92f;

			if (vel.x > VEL_MAX_INI) vel.x = VEL_MAX_INI;
			if (vel.x < -VEL_MAX_INI) vel.x = -VEL_MAX_INI;

			corpo.move(vel.x, vel.y);

			noChao = false;
		}

		void Inimigo::persegue(sf::Vector2f posJogador, sf::Vector2f posInimigo)
		{
			if (!noChao)
				vel.y += GRAVIDADE;

			if ((posInimigo.x - posJogador.x) > 0)
				vel.x -= vel.x;

			else if ((posInimigo.x - posJogador.x) < 0)
				vel.x += vel.x;
			else
				vel.x *= 8;

			if (vel.x > VEL_MAX_INI)
				vel.x = VEL_MAX_INI;
			if (vel.x < -VEL_MAX_INI)
				vel.x = -VEL_MAX_INI;

			if ((posInimigo.y - posJogador.y) > 0)
			{
				vel.y -= 10.0;
				noChao = false;
			}

			corpo.move(vel.x, vel.y);

			noChao = false;

		}

		void Inimigo::mover()
		{
			sf::Vector2f posInimigo = corpo.getPosition();

			if (!LJogs)
			{
				movimentoaleatorio();
				return;
			}

			bool encontrou = false;
			auto itr = LJogs->get_Primeiro();
			while (itr != NULL)
			{
				Entidades::Entidade* e = *itr;
				Entidades::Personagens::Jogador* jog = dynamic_cast<Entidades::Personagens::Jogador*>(e);
				if (jog)
				{
					sf::Vector2f posJogador = jog->get_posicao();

					if (std::fabs(posInimigo.x - posJogador.x) < RAIOX &&
						std::fabs(posInimigo.y - posJogador.y) < RAIOY)
					{
						persegue(posJogador, posInimigo);
						encontrou = true;
						break;
					}
				}
				itr++;
			}

			if (!encontrou)
				movimentoaleatorio();
		}

		void Inimigo::colidir(Obstaculos::Obstaculo* pObs, std::string direcao)
		{
			if (pObs->get_danoso())
				receber_dano(dano);

			if (direcao == "Embaixo" || direcao == "Abaixo")
			{
				noChao = true;
				vel.y = 0.0f;
			}
			else if (direcao == "Cima" || direcao == "Acima")
			{
				vel.y = 0.0f;
			}
			else if (direcao == "Esquerda")
			{
				vel.x = 0.0f;
			}
			else if (direcao == "Direita")
			{
				vel.x = 0.0f;
			}
		}
	}
}