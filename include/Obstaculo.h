#pragma once

#include "Entidades.h"

#define OBSTACULO_TAMANHO 20

namespace Entidades
{

    namespace Personagens
    {
        class Jogador;
	}

    namespace Obstaculos
    {
        class Obstaculo : public Entidade
        {
        protected:
            sf::RectangleShape corpo;
            bool existir;
            bool danoso;
        public:
            Obstaculo(int index = -1, sf::Vector2f pos);
            ~Obstaculo();
            virtual void executar() = 0;
            virtual void mover();
   
            void desenhar();
            virtual void obstaculizar(Entidades::Entidade* outra, std::string direcao = "") = 0;
			virtual void salvar(std::ofstream& arquivo) override {}
			void infligir_dano(int dmg) {}
            void set_vivo(bool a) { existir = a; }
            const bool get_vivo() const { return existir; }
            sf::Vector2f get_posicao() { return corpo.getPosition(); }
            sf::Vector2f get_tamanho() { return corpo.getSize(); }
            void set_posicao(sf::Vector2f pos) { corpo.setPosition(pos); }
			void set_danoso(bool d) { danoso = d; }
            const bool get_danoso() const { return danoso; }
			
        };
    }

}