#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

#define LARGURA 1200
#define ALTURA 800

namespace Gerenciadores
{
	class GerenciadorGrafico
	{
	private:
		sf::RenderWindow* janela;	
		sf::View cam;



		//Sigleton
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


