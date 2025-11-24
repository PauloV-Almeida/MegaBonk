#pragma once

#include "Entidades.h"


namespace Entidades
{
	class Projetil : public Entidade
	{
	protected:
		int tempoVida;
		sf::RectangleShape corpo;
		bool ativo;
		int dano;
		bool vivo;
	public:
		Projetil(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Vector2f velocity = sf::Vector2f(50.f, 50.f), float tempo = 100.f);
		Projetil(bool alv, sf::Vector2f pos, sf::Vector2f velocity, float dmg, float radius, float lftm, bool ativo);
		~Projetil();
		

		void executar();
		void desenhar();
		void mover();
		void colidir(Entidade* outra, std::string direcao = "");
		void calular_colisao();
		sf::Vector2f get_posicao() { return corpo.getPosition(); }
		void infligir_dano(int dmg) { tempoVida -= dmg; }
		void set_vivo(bool a);
		//sf::Vector2f get_tamanho() { return sf::Vector2f(corpo.getRaio()*2, corpo.getRoio()*2); }
		void set_posicao(sf::Vector2f pos) { corpo.setPosition(pos); }
		void set_ativo(bool a) { ativo = a; }
		float get_tempoVida() const { return tempoVida; }
		void set_Cor(sf::Color c) { corpo.setFillColor(c); }
		const int get_dano() const { return dano; }
		const bool get_vivo() const { return vivo; }
		void salvar(std::ofstream& arquivo);
	};
}

