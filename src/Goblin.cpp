#include "../include/Goblin.h"

namespace Entidades
{
	namespace Personagens
	{

		Goblin::Goblin(bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, float dmg, sf::Vector2f tam, float fur):
			Inimigo(1, pos, velo, tam),
			furia(fur)
		{
			dano = dmg;
			n_vidas = nV;
			texturas = pGG->carregar_texturas("./assets/Esqueleto.png");
			corpo.setTexture(texturas);
			vivo = viv;

		}
		Goblin::~Goblin()
		{
		}
		void Goblin::executar()
		{
			mover();
			desenhar();
		}
		void Goblin::danificar(Jogador* p)
		{
			receber_dano(p->get_dano());

			vel.y -= 5.f;
			corpo.setPosition(corpo.getPosition() + sf::Vector2f(2.f * vel.x / 10, 2.f * vel.y / 10));

		}

		void Goblin::colidir(Jogador* pJog, std::string direcao)
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
			dano *= furia;
		}

		void Goblin::desenhar()
		{
			pGG->desenhar(&corpo);
		}
	}
}