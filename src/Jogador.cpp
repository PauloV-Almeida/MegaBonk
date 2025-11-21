#include "../include/Jogador.h"

namespace Entidades
{
	namespace Personagens
	{
		Jogador::Jogador(int indice, sf::Vector2f pos, sf::Vector2f velo, sf::Vector2f tam) :
			ataque_corpo(sf::Vector2f(tam.x * 2, tam.y * 2)),
			atacando(false),
			Personagem(0, pos, velo, tam),
			venceu(false),
			dano(0),
			id_jogador(indice),
			direita(true)
		{
			ataque_corpo.setOrigin(ataque_corpo.getSize().x / 2, ataque_corpo.getSize().y / 2);
			ataque_corpo.setTexture(pGG->carregar_texturas("./assets/jogador1.png"));
			n_vidas = 20;
			if (id_jogador == 1)
			{
				texturas = pGG->carregar_texturas("./assets/jogador1.png");
			}
			else if (id_jogador == 2)
			{
				texturas = pGG->carregar_texturas("./assets/jogador1.png");
			}

			corpo.setTexture(texturas);
		}

		Jogador::Jogador(int indice, bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, sf::Vector2f tam) :
			ataque_corpo(corpo.getSize() * 2.f),
			atacando(false),
			Personagem(0, pos, velo, tam),
			venceu(false),
			dano(0),
			id_jogador(indice),
			direita(true),
			ataque_direcao("Acima")
		{
			vivo = viv;
			n_vidas = nV;

			ataque_corpo.setOrigin(ataque_corpo.getSize().x / 2, ataque_corpo.getSize().y / 2);
			if (id_jogador == 1)
			{
				pGG->carregar_texturas("./assets/jogador1-esquerda.png");
				texturas = pGG->carregar_texturas("./assets/jogador1-direita.png");
			}
			else if (id_jogador == 2)
			{
				pGG->carregar_texturas("./assets/jogador1-esquerda.png");
				texturas = pGG->carregar_texturas("./assets/jogador1-direita.png");
			}
			corpo.setTexture(texturas);

			texturas = pGG->carregar_texturas("./assets/jogador1.png");
			ataque_corpo.setTexture(texturas);
		}

		Jogador::~Jogador()
		{

		}

		void Jogador::desenhar()
		{
			if (vivo)
			{
				if (atacando)
				{
					if (ataque_direcao == "Direita")
					{
						ataque_corpo.rotate(90);
						pGG->desenhar(&ataque_corpo);
						ataque_corpo.rotate(-90);
					}
					else if (ataque_direcao == "Esquerda")
					{
						ataque_corpo.rotate(-90);
						pGG->desenhar(&ataque_corpo);
						ataque_corpo.rotate(90);
					}
					else if (ataque_direcao == "Abaixo")
					{
						ataque_corpo.rotate(180);
						pGG->desenhar(&ataque_corpo);
						ataque_corpo.rotate(180);
					}
					else
					{
						pGG->desenhar(&ataque_corpo);
					}
					atacando = false;
				}
				pGG->desenhar(&corpo);
			}
		}

		void Jogador::executar()
		{
			if (n_vidas <= 0)
				vivo = false;

			// aplica gravidade (comportamento da Entidade base)
			Entidade::mover();

			// processa entrada e altera velocidade horizontal/vertical
			mover();

			// processa ataque (pode desenhar ataque)
			ataque();

			// aplica velocidade à posição (movimenta o corpo)
			corpo.setPosition(corpo.getPosition() + vel);
		}

		void Jogador::mover(char direcao)
		{
			// constante de velocidade vertical de voo (ajuste conforme necessário)
			const float VOAR_SPEED = 5.f;
			// aceleração horizontal (usa a variável 'velocidade' definida na Entidade)
			const float H_ACCEL = 2.f * velocidade;
			// amortecimento quando nenhuma tecla horizontal está pressionada
			const float FRICTION = 0.80f;

			// --- MOVIMENTO VERTICAL ---
			if (id_jogador == 1)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					vel.y = -VOAR_SPEED;
				}
			}
			else if (id_jogador == 2)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					vel.y = -VOAR_SPEED;
				}
			}

			// --- MOVIMENTO HORIZONTAL (verifica independemente do vertical) ---
			if (id_jogador == 1)
			{
				// mover para a direita
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					vel.x += H_ACCEL;
					if (vel.x > VEL_MAX) vel.x = VEL_MAX;
					if (!direita)
					{
						corpo.setTexture(pGG->carregar_texturas("./assets/jogador1-direita.png"));
						direita = true;
					}
				}
				// mover para a esquerda
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					vel.x -= H_ACCEL;
					if (vel.x < -VEL_MAX) vel.x = -VEL_MAX;
					if (direita)
					{
						corpo.setTexture(pGG->carregar_texturas("./assets/jogador1-esquerda.png"));
						direita = false;
					}
				}
				else
				{
					// amortecimento quando nenhuma tecla horizontal é pressionada
					vel.x *= FRICTION;
					if (std::abs(vel.x) < 0.05f) vel.x = 0.f;
				}
			}
			else if (id_jogador == 2)
			{
				// direita
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					vel.x += H_ACCEL;
					if (vel.x > VEL_MAX) vel.x = VEL_MAX;
					if (!direita)
					{
						corpo.setTexture(pGG->carregar_texturas("./assets/jogador1-direita.png"));
						direita = true;
					}
				}
				// esquerda
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					vel.x -= H_ACCEL;
					if (vel.x < -VEL_MAX) vel.x = -VEL_MAX;
					if (direita)
					{
						corpo.setTexture(pGG->carregar_texturas("./assets/jogador1-esquerda.png"));
						direita = false;
					}
				}
				else
				{
					vel.x *= FRICTION;
					if (std::abs(vel.x) < 0.05f) vel.x = 0.f;
				}
			}
		}

		void colidir(Inimigo* pIni, std::string direcao);
		void colidir(Obstaculos::Obstaculo* pObs, std::string direcao)

		void Jogador::ataque()
		{
			if ((id_jogador == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) ||
				(id_jogador == 2 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)))
			{
				return;
			}
			dano = DMG;
			atacando = true;

			std::string direcao = "";
			if (id_jogador == 1)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					direcao = "Acima";
					ataque_direcao = "Acima";
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					direcao = "Esquerda";
					ataque_direcao = "Esquerda";
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					direcao = "Direita";
					ataque_direcao = "Direita";
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					direcao = "Abaixo";
					ataque_direcao = "Abaixo";
				}

			}
			else if (id_jogador == 2)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					direcao = "Acima";
					ataque_direcao = "Acima";
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					direcao = "Esquerda";
					ataque_direcao = "Esquerda";
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					direcao = "Direita";
					ataque_direcao = "Direita";
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					direcao = "Abaixo";
					ataque_direcao = "Abaixo";
				}
			}
			if (direcao == "Acima")
			{
				ataque_corpo.setPosition(sf::Vector2f(corpo.getPosition().x, corpo.getPosition().y - corpo.getSize().y / 2 - ataque_corpo.getSize().y / 2));
			}
			else if (direcao == "Direita")
			{
				ataque_corpo.setPosition(sf::Vector2f(corpo.getPosition().x + corpo.getSize().x / 2 + ataque_corpo.getSize().x / 2, corpo.getPosition().y));
			}
			if (direcao == "Abaixo")
			{
				ataque_corpo.setPosition(sf::Vector2f(corpo.getPosition().x, corpo.getPosition().y + corpo.getSize().y / 2 + ataque_corpo.getSize().y / 2));
			}
			else if (direcao == "Esquerda")
			{
				ataque_corpo.setPosition(sf::Vector2f(corpo.getPosition().x - corpo.getSize().x / 2 - ataque_corpo.getSize().x / 2, corpo.getPosition().y));
			}
			pGG->desenhar(&ataque_corpo);

			dano = 0;
		}

	}//Personagens
}