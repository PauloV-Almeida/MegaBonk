#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>

#define LARGURA 1200
#define ALTURA 720

namespace Gerenciadores
{
	class GerenciadorGrafico
	{
	private:
		sf::RenderWindow* janela;	

		//
		static GerenciadorGrafico* instance;
		GerenciadorGrafico();
	public:
		
		~GerenciadorGrafico();
		static GerenciadorGrafico* get_instance();
		sf::RenderWindow* get_janela();

		void desenhar(sf::RectangleShape corpo);
		void desenhar(sf::CircleShape corpo);
		void mostrar();
		void limpar();
		void fechaJanela();
		const bool abreJanela();

	};
}


