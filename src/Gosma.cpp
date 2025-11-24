#include "../include/Gosma.h"
#include "../include/Jogador.h"


namespace Entidades
{
    namespace Obstaculos
    {
        Gosma::Gosma(sf::Vector2f pos,float len) :
            Obstaculo(12, pos),
			lentidao(len)
        {

            texturas = pGG->carregar_texturas("./assets/obstaculo3.png");
            corpo.setTexture(texturas);
            
        }
        Gosma:: ~Gosma()
        {

        }

        void Gosma::obstaculizar(Entidades::Entidade* outra, std::string direcao)
        {
            // Aplica lentid�o ao jogador que colidiu com a gosma.
             // Usa dynamic_cast para identificar Jogador (tanto id 1 quanto 2).
            if(outra->get_id() == 1 || outra->get_id() == 2)
            {
                auto pJog = dynamic_cast<Entidades::Personagens::Jogador*>(outra);
                if (pJog)
                {
                    sf::Vector2f v = pJog->get_vel();
                    if (lentidao != 0.f)
                    {
                        v.x /= lentidao;
                        v.y /= lentidao;
                    }
                    else
                    {
                        // Se por acaso lentidao for zero, zera velocidade para evitar divis�o por zero.
                        v = sf::Vector2f(0.f, 0.f);
                    }
                    pJog->set_vel(v);
                }
			}
            
        }
        void Gosma::executar()
        {
            mover();
        }
        void Gosma::mover()
        {

            vel.y += GRAVIDADE;
            if (parado)
            {
                vel.y -= GRAVIDADE;
            }
            corpo.setPosition(corpo.getPosition() + vel);

        }
    }
}