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

        sf::Vector2f vel;
        static sf::Vector2f posJogador;
        int dano;
        Gerenciadores::GerenciadorColisoes* gColisao;

    public:
        Entidade(int indice = -1, sf::Vector2f velo = sf::Vector2f(0.f, 0.f));
        virtual ~Entidade();
        virtual void desenhar() = 0;
        virtual void executar() = 0;
        virtual void mover(char direcao = ' ') { vel.y += GRAVIDADE; };

        virtual void set_posicao(sf::Vector2f pos) = 0;

        void set_vel(sf::Vector2f v) { vel = v; }
        void set_GerenciadorColisao(Gerenciadores::GerenciadorColisoes* cm) { gColisao = cm; }

        

        sf::Vector2f get_vel() { return vel; }

        virtual sf::Vector2f get_posicao() = 0;
        virtual sf::Vector2f get_tamanho() = 0;
        const int get_id() const { return id; }

        virtual void set_vivo(bool a) = 0;
        virtual const bool get_vivo() const { return true; }

        void set_dano(int d) { dano = d; }
        int get_dano() { return dano; }
    };
}
