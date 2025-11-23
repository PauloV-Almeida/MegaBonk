#include "../include/Espinhos.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"

namespace Entidades
{
    namespace Obstaculos
    {
        Espinhos::Espinhos(sf::Vector2f pos, bool veri) :
            Obstaculo(11, pos),
            pVerifica(veri)
        {
            if (pVerifica)
                corpo.setFillColor(sf::Color::Cyan);
            else
            {
                texturas = pGG->carregar_texturas("./assets/obstaculo3.png");
                corpo.setTexture(texturas);
            }
        }
        Espinhos:: ~Espinhos()
        {

        }
        void Espinhos::executar()
        {
            mover();
        }
        void Espinhos::mover()
        {
            if (pVerifica)
            {
                // plataforma móvel: aplica gravidade/movimento
                vel.y += GRAVIDADE;
                if (deCastigo)
                {
                    vel.y -= GRAVIDADE;
                }
                corpo.setPosition(corpo.getPosition() + vel);
            }
            else
            {
                // plataforma fixa: garante velocidade zero (não cai)
                vel = sf::Vector2f(0.f, 0.f);
            }
        }
        void Espinhos::obstaculizar(Entidades::Personagens::Jogador* p)
        {
			p->receber_dano(dano);
            p->set_vel(sf::Vector2f(0.f, -5.f));
        }
    }
} 