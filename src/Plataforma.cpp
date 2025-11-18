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
                texturas = pGG->carregar_texturas("./assets/obstaculo3.png");
                corpo.setTexture(texturas);
            }
        }
        Plataforma:: ~Plataforma()
        {

        }
        //void Plataforma::obstaculizar(Entidade* outro, std::string  direcao)
        
        void Plataforma::executar()
        {
            mover();
        }
        void Plataforma::mover()
        {
            vel.y += GRAVIDADE;
            if (deCastigo)
            {
                vel.y -= GRAVIDADE;
            }
            corpo.setPosition(corpo.getPosition() + vel);
        }
    }
}