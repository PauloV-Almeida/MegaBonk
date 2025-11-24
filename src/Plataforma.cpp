#include "../include/Plataforma.h"
#include "../include/Jogador.h"


namespace Entidades
{
    namespace Obstaculos
    {
        Plataforma::Plataforma(sf::Vector2f pos, bool veri) :
            Obstaculo(11, pos),
            verifica(veri),
			echao(false)
        {
            if (verifica)
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

        void Plataforma::obstaculizar(Entidades::Entidade* outra, std::string direcao = "")
        {
            if (verifica)
            {
                Entidades::Personagens::Jogador* pJog = dynamic_cast<Entidades::Personagens::Jogador*>(outra);
                if (pJog != nullptr)
                {
                    pJog->set_venceu(true);
                }
            }
        }
        void Plataforma::executar()
        {
            mover();
        }
        void Plataforma::mover()
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