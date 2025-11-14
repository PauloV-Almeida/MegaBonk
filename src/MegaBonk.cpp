#include "../include/Megabonk.h"

/*MegaBonk::MegaBonk() :
	pGG(Gerenciadores::GerenciadorGrafico::get_instance()),
	pGC(Gerenciadores::GerenciadorColisoes::get_instance())
	//,pGE(Gerenciadores::GerenciadorEventos::get_instance()),
	//pGEst(Gerenciadores::GerenciadorEstados::get_instance())
{
	executar();
}*/

MegaBonk::MegaBonk() :
	pGG(Gerenciadores::GerenciadorGrafico::get_instance()),
	pGC(Gerenciadores::GerenciadorColisoes::get_instance()),
	jogador(nullptr),
	plataformaCentral(nullptr)
{
	jogador = new Entidades::Personagens::Jogador(
		sf::Vector2f(600.f, 300.f),
		sf::Vector2f(7.f, 7.f),
		sf::Vector2f(50.f, 50.f)
	);
	plataformaCentral = new Entidades::Obstaculos::Plataforma(sf::Vector2f(600.f, 500.f));
	plataformaCentral->setTam(sf::Vector2f(300.f, 20.f));
	plataformaCentral->setColor(sf::Color::Red);
	p1 = new Entidades::Obstaculos::Plataforma(sf::Vector2f(700.f, 400.f));
	p1->setTam(sf::Vector2f(20.f, 300.f));
	p1->setColor(sf::Color::Magenta);
	p2 = new Entidades::Obstaculos::Plataforma(sf::Vector2f(350.f, 350.f));
	p2->setTam(sf::Vector2f(70.f, 70.f));
	p2->setColor(sf::Color::Yellow);
	executar();
}

MegaBonk::~MegaBonk()
{
}

void MegaBonk::executar()
{
	pGC->incluirObstaculo(plataformaCentral);
	pGC->incluirObstaculo(p1);
	pGC->incluirObstaculo(p2);
	pGC->setJogadores(jogador);
	while (pGG->abreJanela()) {
		pGG->limpar();

		pGC->executar();
		//pGE->executar();
		//pGEst->executar();
		jogador->executar();
		plataformaCentral->desenhar();
		p1->desenhar();
		p2->desenhar();

		pGG->mostrar();
	}
}