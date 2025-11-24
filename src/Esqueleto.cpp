#include "../include/Esqueleto.h"

namespace Entidades
{
	namespace Personagens
	{
		
		Esqueleto::Esqueleto(bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, float dmg, sf::Vector2f tam, float emp) :
			Inimigo(1, pos, velo, tam),
			empurrar(emp)
		{
			nivel_maldade = dmg;
			n_vidas = nV;
			texturas = pGG->carregar_texturas("./assets/Esqueleto.png");
			corpo.setTexture(texturas);
			vivo = viv;
			
		}
		Esqueleto::~Esqueleto()
		{
		}
		void Esqueleto::executar()
		{
			if(velocidade > 0)
			{
				vel.y += GRAVIDADE;
				if (empurrar > 0)
					vel.x += VELOCIDADE/4;
				else
					vel.x -= VELOCIDADE / 4;
				corpo.setPosition(corpo.getPosition() + sf::Vector2f(velocidade * vel.x / 10, velocidade * vel.y / 10));
			}
		}
		
		void Esqueleto::danificar(Entidade* outra, std::string direcao)
		{
			int indice = outra->get_id();
			sf::Vector2f pos = outra->get_posicao();
			sf::Vector2f tam = outra->get_tamanho();

			switch (indice)
			{
			case 0:
				if (!static_cast<Entidades::Personagens::Jogador*>(outra)->get_dano())
				{
					if(direcao == "Direita")
					{ }
				}
			default:
				break;
			}
		}

	}
}