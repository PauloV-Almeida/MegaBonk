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
		}
		void Esqueleto::danificar()
		{
			if (velocidade > 0)
			{
				vel.y -= 5.f;
				corpo.setPosition(corpo.getPosition() + sf::Vector2f(velocidade * vel.x / 10, velocidade * vel.y / 10));
			}
			

		}
	}
}