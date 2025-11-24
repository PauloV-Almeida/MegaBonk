#include "../include/Espinhos.h"
#include "../include/Jogador.h"


namespace Entidades
{
    namespace Obstaculos
    {
        Espinhos::Espinhos(sf::Vector2f pos, int dmg) :
            Obstaculo(13, pos),
			dano_espinhos(dmg)
        {
            
            texturas = pGG->carregar_texturas("./assets/obstaculo3.png");
            corpo.setTexture(texturas);
           
        }
        Espinhos:: ~Espinhos()
        {

        }
        void Espinhos::obstaculizar(Entidades::Entidade* outra, std::string direcao)
        {
            if (outra->get_id() == 1 || outra->get_id() == 2)
            {
                auto pJog = dynamic_cast<Entidades::Personagens::Jogador*>(outra);
                if (pJog)
                {
                    pJog->receber_dano(dano_espinhos);
                }
            }
        }
        void Espinhos::executar()
        {
            mover();
        }
        void Espinhos::mover()
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