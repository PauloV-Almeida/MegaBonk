#pragma once

#include "Obstaculo.h"

namespace Entidades
{

    namespace Obstaculos
    {
        class Gosma : public Obstaculo
        {
        private:
            float lentidao;
        public:
            Gosma(sf::Vector2f pos, float len = 4);
            ~Gosma();
            void obstaculizar(Entidades::Entidade* outra, std::string direcao = "");
            void executar();
            void mover();
        };
    }
}