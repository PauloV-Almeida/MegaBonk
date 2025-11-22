#include "../include/ArvoreMonstro.h"

namespace Entidades
{
	namespace Personagens
	{

		ArvoreMonstro::ArvoreMonstro(bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, float dmg, sf::Vector2f tam, float tempo) :
			Inimigo(1, pos, velo, tam),
			tempovinha(tempo)
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
			projetar();
			desenhar();
		}
		void ArvoreMonstro::danificar()
		{
			if (velocidade > 0)
			{
				vel.y -= 5.f;
				corpo.setPosition(corpo.getPosition() + sf::Vector2f(velocidade * vel.x / 10, velocidade * vel.y / 10));
			}


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