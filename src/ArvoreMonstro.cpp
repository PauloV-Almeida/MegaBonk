#include "../include/ArvoreMonstro.h"

namespace Entidades
{
	namespace Personagens
	{

		ArvoreMonstro::ArvoreMonstro(bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, float dmg, sf::Vector2f tam, int delay_ataque) :
			Inimigo(3, pos, velo, tam),
			pProjetil(nullptr),
			delay_ataque(delay_ataque)
		{
			dano = dmg;
			n_vidas = nV;
			texturas = pGG->carregar_texturas("./assets/Esqueleto.png");
			corpo.setTexture(texturas);
			vivo = viv;

		}
		ArvoreMonstro::~ArvoreMonstro()
		{
		}
		void ArvoreMonstro::executar()
		{
			mover();
			
			desenhar();
		}
		void ArvoreMonstro::danificar(Jogador* p)
		{
			receber_dano(p->get_dano());

			vel.y -= 5.f;
			corpo.setPosition(corpo.getPosition() + sf::Vector2f(2.f * vel.x / 10, 2.f * vel.y / 10));

		}

		void ArvoreMonstro::colidir(Jogador* pJog, std::string direcao)
		{
			pJog->receber_dano(dano);
			if (direcao == "Embaixo")
			{
				noChao = true;
				vel.y = 0.0f;
			}
			else if (direcao == "Cima")
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

		void ArvoreMonstro::desenhar()
		{
			pGG->desenhar(&corpo);
		}

		void ArvoreMonstro::projetar()
		{

		}
	}
}