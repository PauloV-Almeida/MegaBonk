#include "../include/Esqueleto.h"

namespace Entidades
{
	namespace Personagens
	{

		Esqueleto::Esqueleto(bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, float dmg, sf::Vector2f tam, float emp) :
			Inimigo(1, pos, velo, tam),
			empurrar(emp)
		{
			dano = dmg;
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
			mover();
			desenhar();
		}
		void Esqueleto::danificar(Jogador* p)
		{
			receber_dano(p->get_dano());

			vel.y -= 5.f;
			corpo.setPosition(corpo.getPosition() + sf::Vector2f(2.f * vel.x / 10, 2.f * vel.y / 10));

		}
		void Esqueleto::colidir(Jogador* pJog, std::string direcao)
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
				pJog->set_vel(pJog->get_vel() + sf::Vector2f(-empurrar, 0.f));
			}
			else if (direcao == "Direita")
			{
				vel.x = 0.0f;
				pJog->set_vel(pJog->get_vel() + sf::Vector2f(empurrar, 0.f));
			}
		}

		void Esqueleto::desenhar()
		{
			pGG->desenhar(&corpo);
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

	}
}
	
