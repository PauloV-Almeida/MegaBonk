#include "../include/GerenciadorGrafico.h"

namespace Gerenciadores
{
	GerenciadorGrafico* GerenciadorGrafico::instance = nullptr;


	GerenciadorGrafico* GerenciadorGrafico::get_instance() {
		if (instance == nullptr) {
			instance = new GerenciadorGrafico();
		}
		return instance;
	}
	GerenciadorGrafico::GerenciadorGrafico(): 
		janela(new sf::RenderWindow(sf::VideoMode(LARGURA, ALTURA), "Megabonk++")),
		texturas()

	{
		janela->setFramerateLimit(60);
	}

	GerenciadorGrafico::~GerenciadorGrafico()
	{
		for (std::map<const std::string, sf::Texture*>::iterator it = texturas.begin(); it != texturas.end(); it++)
			delete it->second;
		texturas.clear();
		delete(janela);
	}

	sf::RenderWindow* GerenciadorGrafico::get_janela() {
		return janela;
	}

	void GerenciadorGrafico::mostrar() {
		if(abreJanela())
			janela->display();
	}

	void GerenciadorGrafico::limpar() {
		if(abreJanela())
			janela->clear();
	}

	void GerenciadorGrafico::desenhar(sf::RectangleShape* corpo) {
		janela->draw(*corpo);
	}

	void GerenciadorGrafico::desenhar(sf::CircleShape* corpo) {
		janela->draw(*corpo);
	}

	void GerenciadorGrafico::fechaJanela() {
		janela->close();
	}

	const bool GerenciadorGrafico::abreJanela() {
		return (janela->isOpen());
	}

}