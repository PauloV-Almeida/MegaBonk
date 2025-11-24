#include "../include/Gosma.h"
#include "../include/Jogador.h"
#include <iostream>

namespace Entidades
{
    namespace Obstaculos
    {
        Gosma::Gosma(sf::Vector2f pos, float len) :
            Obstaculo(12, pos),
            lentidao(len)
        {

            texturas = pGG->carregar_texturas("./assets/gosma.png");
            corpo.setTexture(texturas);

        }
        Gosma:: ~Gosma()
        {

        }

        void Gosma::obstaculizar(Entidades::Entidade* outra, std::string direcao)
        {
            // Identifica diretamente se 'outra' é Jogador (dynamic_cast) — não confiar em get_id()
            auto pJog = dynamic_cast<Entidades::Personagens::Jogador*>(outra);
            if (!pJog) return;

            // Debug (remova após testar)
            std::cerr << "[Gosma] obstaculizar chamado para jogador ptr=" << pJog << " factor=" << lentidao << std::endl;

            // Redução imediata da velocidade atual (visível já neste frame)
            sf::Vector2f v = pJog->get_vel();
            if (lentidao != 0.f)
            {
                v.x /= lentidao;
                v.y /= lentidao;
            }
            else
            {
                v = sf::Vector2f(0.f, 0.f);
            }
            pJog->set_vel(v);

            // Aplica efeito persistente: reduz velocidade máxima por N frames.
            constexpr int DURATION_FRAMES = 60;
            pJog->aplicar_lentidao(lentidao, DURATION_FRAMES);

            std::cerr << "[Gosma] aplicou lentidao: speedModifier=" << (1.0f / lentidao) << " dur=" << DURATION_FRAMES << std::endl;
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