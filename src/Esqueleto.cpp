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
			if (velocidade > 0)
			{
				if (parado)
				{
					vel.y -= 5.f;
				}
				else 
					vel.y += GRAVIDADE;
				if(vel.y>GRAVIDADE)
					vel.y = GRAVIDADE;
				mover();
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
					{ 
						outra->infligir_dano(nivel_maldade);
						vel.x -= empurrar;

					}else if(direcao == "Esquerda")
					{
						outra->infligir_dano(nivel_maldade);
						vel.x += empurrar;
					}
					else if (direcao == "Acima")
					{
						outra->infligir_dano(nivel_maldade);
						vel.y += empurrar;
					}
					else if (direcao == "Abaixo")
					{
						outra->infligir_dano(nivel_maldade);
						vel.y -= empurrar;
					}
				}
				else
				{
					if (direcao == "Direita")
					{
						outra->infligir_dano(nivel_maldade);
						vel.x -= empurrar;

					}
					else if (direcao == "Esquerda")
					{
						outra->infligir_dano(nivel_maldade);
						vel.x += empurrar;
					}
					else if (direcao == "Acima")
					{
						outra->infligir_dano(nivel_maldade);
						vel.y += empurrar;
					}
					else if (direcao == "Abaixo")
					{
						outra->infligir_dano(nivel_maldade);
						vel.y -= empurrar;
					}
				}
				break;
			case 11:
				if (direcao == "Direita")
				{
					vel.x = -VELOCIDADE;
					empurrar = -EMPURRAR_JOGADOR;
				}
				else if(direcao == "Esquerda")
				{
					vel.x = VELOCIDADE;
					empurrar = EMPURRAR_JOGADOR;
				}
				break;
			default:
				break;
			}
			executar();
		}
	void Esqueleto::salvar(std::ofstream& arquivo)
	{
		if (!arquivo.is_open())
		{
			std::cout << "Error: Cannot open enemy file!" << std::endl;
			return;
		}
		arquivo << id << std::endl;
		if (vivo)
			arquivo << 1 << std::endl;
		else
			arquivo << 0 << std::endl;
		arquivo << n_vidas << std::endl << nivel_maldade << std::endl
			<< corpo.getPosition().x << std::endl << corpo.getPosition().y << std::endl
			<< vel.x << std::endl << vel.y << std::endl
			<< corpo.getSize().x << std::endl << corpo.getSize().y << std::endl
			<< empurrar << std::endl << std::endl;
	}
	

	}//Personagens
}