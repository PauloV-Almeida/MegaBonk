#include "../include/Deserto.h"
namespace Fases
{
	Deserto::Deserto():
		Fase(1),
		fim(0)
	{
		corpo.setSize(sf::Vector2f(900.f, 600.f));
		corpo.setOrigin(sf::Vector2f(0.f, 0.f));
		texturas = pGG->carregar_texturas("./assets/Deserto.png");
		corpo.setTexture(texturas);

		Entidades::Personagens::Jogador* p1 = new Entidades::Personagens::Jogador(1, sf::Vector2f(200.f, 450.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(50.f, 50.f));
		p1->set_GerenciadorColisao(&gColisoes);
		jogadores.add(p1);
	}

	Deserto::Deserto(int n_jogadores) :
		Fase(6),
		fim(TEMPOFIM)
	{
		corpo.setSize(sf::Vector2f(900.f, 600.f));
		corpo.setOrigin(sf::Vector2f(0.f, 0.f));
		texturas = pGG->carregar_texturas("./assets/Deserto.png");
		corpo.setTexture(texturas);

		for (int i = 0; i < n_jogadores; ++i)
		{
			float x = 150.f + i * 120.f;
			float y = 450.f;
			Entidades::Personagens::Jogador* p = new Entidades::Personagens::Jogador(i + 1, sf::Vector2f(x, y), sf::Vector2f(0.f, 0.f), sf::Vector2f(50.f, 50.f));
			p->set_GerenciadorColisao(&gColisoes);
			jogadores.add(p);
		}
	}

	Deserto::~Deserto()
	{
	}

	void Deserto::executar()
	{
		jogadores.executar();
		inimigos.executar();
		obstaculos.executar();

		desenhar();
		// desenha um chão simples na base do cenário
		sf::RectangleShape chao;
		float largura = corpo.getSize().x;
		const float alturaChao = 80.f;
		chao.setSize(sf::Vector2f(largura, alturaChao));
		chao.setOrigin(sf::Vector2f(0.f, 0.f));
		chao.setPosition(sf::Vector2f(0.f, corpo.getSize().y - alturaChao));
		chao.setFillColor(sf::Color(150, 90, 19)); // marrom
		pGG->desenhar(&chao);
		
		jogadores.desenhar();
		inimigos.desenhar();
		obstaculos.desenhar();
		
	}
}