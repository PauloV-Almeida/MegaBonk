#include "../include/Plataforma.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"

namespace Entidades
{
    namespace Obstaculos
    {
        Plataforma::Plataforma(sf::Vector2f pos, bool veri) :
            Obstaculo(11, pos)
        {
            pVerifica = veri;
            if (veri)
                corpo.setFillColor(sf::Color::Cyan);
            else
            {
                texturas = pGG->carregar_texturas("carregar png");
                corpo.setTexture(texturas);
            }
        }
        Plataforma:: ~Plataforma()
        {

        }
        void Plataforma::colidir(Entidade* outro, std::string  direcao)
        {
            if (pVerifica)
            {
                Entidades::Personagens::Jogador* jogador = dynamic_cast<Entidades::Personagens::Jogador*>(outro);
                /*if (jogador != nullptr)
                {
                    jogador->set_win(true);
                }*/
            }
        }
        void Plataforma::executar()
        {
            mover();
        }
        void Plataforma::mover()
        {
            vel.y += GRAVIDADE;

            corpo.setPosition(corpo.getPosition() + vel);
        }
    }
}