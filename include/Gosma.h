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
        class Gosma : public Obstaculo
        {
        private:
            bool pVerifica;
        public:
            Gosma(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), bool veri = false);
            ~Gosma();
            void obstaculizar(Entidades::Personagens::Jogador* p);
            void executar();
            void mover();
        };
    }
}