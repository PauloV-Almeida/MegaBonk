#pragma once

#include "Obstaculo.h"

namespace Entidades
{

    namespace Personagens
    {
        class Jogador;
    }

    namespace Obstaculos
    {
        class Espinhos : public Obstaculo
        {
        private:
            bool pVerifica;
        public:
            Espinhos(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), bool veri = false);
            ~Espinhos();
            void obstaculizar(Entidades::Personagens::Jogador* p);
            void executar();
            void mover();
        };
    }
}