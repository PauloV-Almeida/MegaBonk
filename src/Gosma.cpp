#include "../include/Gosma.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"

namespace Entidades
{
    namespace Obstaculos
    {
        Gosma::Gosma(sf::Vector2f pos, bool veri) :
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
        Gosma:: ~Gosma()
        {

        }
        void Gosma::executar()
        {
            mover();
        }
        void Gosma::mover()
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
        void Gosma::obstaculizar(Entidades::Personagens::Jogador* p)
        {
            p->set_vel(sf::Vector2f(p->get_vel().x * 0.7, p->get_vel().y));
        }
    }
}