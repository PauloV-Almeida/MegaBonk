#pragma once

#include "Ente.h"
//#include "../observers/Observer.h"

#include <fstream>

namespace Gerenciadores
{
    class GerenciadorColisoes;
}

namespace Entidades
{
    class Entidade : public Ente
    {
    protected:
        const int id;
        static int contar;

        static float velocidade;
        sf::Vector2f vel;
        static sf::Vector2f posJogador;

        //Gerenciadores::GerenciadorColisoes* gColisao;

    public:
        Entidade(int indice = -1, sf::Vector2f velo = sf::Vector2f(0.f, 0.f));
        virtual ~Entidade();
        virtual void desenhar() = 0;
        virtual void executar() = 0;
        virtual void set_posicao(sf::Vector2f pos) = 0;
        

    };
}
