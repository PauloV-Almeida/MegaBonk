#include "GerenciadorGrafico.h"

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
		janela(new sf::RenderWindow(sf::VideoMode(LARGURA, ALTURA), "Megabonk++"))

	{

	}

	GerenciadorGrafico::~GerenciadorGrafico()
	{
		delete(janela);
	}

	sf::RenderWindow* GerenciadorGrafico::get_janela() {
		return janela;
	}

	void GerenciadorGrafico::desenhar(sf::RectangleShape corpo) {
		janela->draw(corpo);
	}

	void GerenciadorGrafico::desenhar(sf::CircleShape corpo) {
		janela->draw(corpo);
	}

	void GerenciadorGrafico::mostrar() {
		if(abreJanela())
			janela->display();
	}

	void GerenciadorGrafico::limpar() {
		if(abreJanela())
			janela->clear();

		sf::Event evento;
		while (janela->pollEvent(evento)) {
			switch (evento.type) {
			case sf::Event::Closed:
				fechaJanela();
				break;
			default:
				break;
			}
		}
	}
	void GerenciadorGrafico::fechaJanela() {
		janela->close();
	}

	const bool GerenciadorGrafico::abreJanela() {
		return (janela->isOpen());
	}

}