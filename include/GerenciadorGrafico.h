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
		std::map<const std::string, sf::Texture*> texturas;

		//Sigleton
		static GerenciadorGrafico* instance;
		GerenciadorGrafico();
	public:
		~GerenciadorGrafico();
		static GerenciadorGrafico* get_instance();
		sf::RenderWindow* get_janela() const;

		void mostrar();
		void limpar();
		void desenhar(sf::RectangleShape* corpo);
		void desenhar(sf::CircleShape* corpo);
		sf::Texture* carregar_texturas(std::string path);

		void fechaJanela();
		const bool abreJanela();

	};
}


