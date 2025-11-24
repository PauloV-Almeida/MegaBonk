#pragma once

#include "Entidades.h"

namespace Entidades
{
	namespace Personagens
	{
		class Personagem : public Entidade
		{
		protected:
			sf::RectangleShape corpo;
			bool vivo;
			int n_vidas;
			bool noChao;
		public:
			Personagem(int indice = -1, sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Vector2f vel = sf::Vector2f(50.f, 50.f), sf::Vector2f tam = sf::Vector2f(0.f, 0.f));
			virtual ~Personagem();
			virtual void executar() = 0;
			virtual void salvar(std::ofstream& arquivo) = 0;
			
			void infligir_dano(int dmg) {
				if (dmg <= 0) return;
				n_vidas -= dmg;
				std::cerr << "[Personagem::infligir_dano] ptr=" << this << " dmg=" << dmg << " vidas_restantes=" << n_vidas << std::endl;
				if (n_vidas <= 0) {
					vivo = false;
					std::cerr << "[Personagem::infligir_dano] personagem morreu ptr=" << this << std::endl;
				}
			}

			void receber_dano(int dmg) {
				n_vidas -= dmg;
				if (n_vidas <= 0) set_vivo(false);
			}

			void set_vivo(bool a) { vivo = a; }
			virtual void desenhar();
			sf::Vector2f get_posicao() { return corpo.getPosition(); }
			sf::Vector2f get_tamanho() { return corpo.getSize(); }
			void set_posicao(sf::Vector2f pos) { corpo.setPosition(pos); }
			const bool get_vivo() const { return vivo; }
			const int get_vidas() const { return n_vidas; }
			void set_noChao(bool nc) { noChao = nc; }
			

		};
	}
}