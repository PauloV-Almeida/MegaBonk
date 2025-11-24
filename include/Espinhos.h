#pragma once

#include "Obstaculo.h"

namespace Entidades
{

    namespace Obstaculos
    {
        class Espinhos : public Obstaculo
        {
        private:
			int dano_espinhos;
        public:
            Espinhos(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), int dmg = 1);
            ~Espinhos();
            void obstaculizar(Entidades::Entidade* outra, std::string direcao = "");
            void executar();
			void mover();
        };
    }
}