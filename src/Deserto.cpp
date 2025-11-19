#include "../include/Deserto.h"
namespace Fases
{
	Deserto::Deserto() :
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

		// cria chão como uma linha de tiles-obstáculo e registra em obstaculos
		float largura = corpo.getSize().x;
		int cols = static_cast<int>(std::ceil(largura / OBSTACULO_TAMANHO));
		float groundY = corpo.getSize().y - (OBSTACULO_TAMANHO / 2.f); // posição central dos tiles

		for (int k = 0; k < cols; ++k)
		{
			Entidades::Obstaculos::Plataforma* tile = new Entidades::Obstaculos::Plataforma(sf::Vector2f(k * OBSTACULO_TAMANHO + (OBSTACULO_TAMANHO / 2.f), groundY));
			tile->set_GerenciadorColisao(&gColisoes);
			Entidades::Entidade* pObs = static_cast<Entidades::Entidade*>(tile);
			obstaculos.add(pObs);
		}

		// REGISTRA obstáculos no gerenciador *após* tê-los criado
		gColisoes.incluirObstaculos(&obstaculos);
		// cria e adiciona um inimigo (Esqueleto) que cairá e colidirá com o chão
		const float esqW = 50.f, esqH = 50.f;
		int spawnCol = cols / 2;
		float spawnX = spawnCol * OBSTACULO_TAMANHO + (OBSTACULO_TAMANHO / 2.f);
		// plataforma está centrada em groundY; para colocar o esqueleto sobre ela:
		float spawnY = groundY - (OBSTACULO_TAMANHO / 2.f) - (esqH / 2.f);
		Entidades::Personagens::Esqueleto* esq = new Entidades::Personagens::Esqueleto(true, 3, sf::Vector2f(spawnX, spawnY), sf::Vector2f(0.f, 0.f), 1.f, sf::Vector2f(esqW, esqH), 0);
		esq->set_GerenciadorColisao(&gColisoes);
		inimigos.add(static_cast<Entidades::Entidade*>(esq));
		// registra inimigos no gerenciador agora que foi adicionado
		gColisoes.incluirInimigos(&inimigos);
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

		// cria chão como uma linha de tiles-obstáculo e registra em obstaculos
		float largura = corpo.getSize().x;
		int cols = static_cast<int>(std::ceil(largura / OBSTACULO_TAMANHO));
		float groundY = corpo.getSize().y - (OBSTACULO_TAMANHO / 2.f); // posição central dos tiles

		for (int k = 0; k < cols; ++k)
		{
			Entidades::Obstaculos::Plataforma* tile = new Entidades::Obstaculos::Plataforma(sf::Vector2f(k * OBSTACULO_TAMANHO + (OBSTACULO_TAMANHO / 2.f), groundY));
			tile->set_GerenciadorColisao(&gColisoes);
			Entidades::Entidade* pObs = static_cast<Entidades::Entidade*>(tile);
			obstaculos.add(pObs);
		}

		// REGISTRA obstáculos no gerenciador *após* tê-los criado
		gColisoes.incluirObstaculos(&obstaculos);

		// cria e adiciona um inimigo (Esqueleto) que cairá e colidirá com o chão
		const float esqW = 50.f, esqH = 50.f;
		int spawnCol = cols / 2;
		float spawnX = spawnCol * OBSTACULO_TAMANHO + (OBSTACULO_TAMANHO / 2.f);
		// plataforma está centrada em groundY; para colocar o esqueleto sobre ela:
		float spawnY = groundY - (OBSTACULO_TAMANHO / 2.f) - (esqH / 2.f);
		Entidades::Personagens::Esqueleto* esq = new Entidades::Personagens::Esqueleto(true, 3, sf::Vector2f(spawnX, spawnY), sf::Vector2f(0.f, 0.f), 1.f, sf::Vector2f(esqW, esqH), 0);
		esq->set_GerenciadorColisao(&gColisoes);
		inimigos.add(static_cast<Entidades::Entidade*>(esq));
		// registra inimigos no gerenciador agora que foi adicionado
		gColisoes.incluirInimigos(&inimigos);
	}

	Deserto::~Deserto()
	{
	}

	void Deserto::executar()
	{
		// atualiza entidades (gravidade, movimento, etc.)
		jogadores.executar();
		inimigos.executar();
		obstaculos.executar();

		// processa colisões (importante: deve ser feito após mover as entidades e antes de desenhar)
		gColisoes.executar();

		// desenha background e entidades (plataformas primeiro, depois jogadores para ficarem por cima)
		desenhar();
		obstaculos.desenhar();
		jogadores.desenhar();
		inimigos.desenhar();
	}
}