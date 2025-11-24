#include "../include/Jogador.h"
#include "../include/GerenciadorColisoes.h"

namespace Entidades
{
	namespace Personagens
	{
		Jogador::Jogador(int indice, sf::Vector2f pos, sf::Vector2f velo, sf::Vector2f tam) :
			ataque_corpo(sf::Vector2f(tam.x * 2, tam.y * 2)),
			atacando(false),
			Personagem(0, pos, velo, tam),
			delay_ataque(0),
			venceu(false),
			dano_ataque(0),
			id_jogador(indice),
			direita(true),
			speedModifier(1.0f),
			slowTimer(0)
		{

			ataque_corpo.setOrigin(ataque_corpo.getSize().x / 2, ataque_corpo.getSize().y / 2);
			ataque_corpo.setTexture(pGG->carregar_texturas("./assets/ataque.png"));
			n_vidas = 20;
			if (id_jogador == 1)
			{
				texturas = pGG->carregar_texturas("./assets/jogador1.png");
			}
			else if (id_jogador == 2)
			{
				texturas = pGG->carregar_texturas("./assets/jogador2.png");
			}

			corpo.setTexture(texturas);
		}

		Jogador::Jogador(int indice, bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, sf::Vector2f tam) :
			ataque_corpo(corpo.getSize() * 2.f),
			atacando(false),
			Personagem(0, pos, velo, tam),
			delay_ataque(0),
			venceu(false),
			dano_ataque(0),
			id_jogador(indice),
			direita(true),
			ataque_direcao("Acima"),
			speedModifier(1.0f),
			slowTimer(0)
		{

			vivo = viv;
			n_vidas = nV;

			ataque_corpo.setOrigin(ataque_corpo.getSize().x / 2, ataque_corpo.getSize().y / 2);
			if (id_jogador == 1)
			{
				pGG->carregar_texturas("./assets/jogador1-esquerda.png");
				texturas = pGG->carregar_texturas("./assets/jogador1.png");
			}
			else if (id_jogador == 2)
			{
				pGG->carregar_texturas("./assets/jogador2-esquerda.png");
				texturas = pGG->carregar_texturas("./assets/jogador2.png");
			}
			corpo.setTexture(texturas);

			texturas = pGG->carregar_texturas("./assets/ataque.png");
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

			// atualiza duração do efeito de lentidão
			if (slowTimer > 0) {
				--slowTimer;
				if (slowTimer <= 0) {
					speedModifier = 1.0f;
					slowTimer = 0;
				}
			}

			mover();
			ataque();

			delay_ataque--;
		}

		void Jogador::mover(char direcao)
		{
			if (id_jogador == 1)
			{
				if (!noChao)
					vel.y += GRAVIDADE;

				// leitura das teclas com comportamento "imediato": define velocidade fixa,
				// e zera quando nenhuma tecla estiver pressionada.
				bool moveEsq = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
				bool moveDir = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

				if (moveEsq && !moveDir) {
					vel.x = -VELOCIDADE * speedModifier;
					if (direita)
					{
						corpo.setTexture(pGG->carregar_texturas("./assets/jogador1-esquerda.png"));
						direita = false;
					}
				}
				else if (moveDir && !moveEsq) {
					vel.x = VELOCIDADE * speedModifier;
					if (!direita)
					{
						corpo.setTexture(pGG->carregar_texturas("./assets/jogador1.png"));
						direita = true;
					}
				}
				else
				{
					// nenhuma tecla horizontal -> parar imediatamente
					vel.x = 0.f;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && noChao)
				{
					vel.y -= 6.0;
					noChao = false;
				}
				corpo.move(vel.x, vel.y);

				// noChao controlado pelo GerenciadorColisoes (colisões setam true para o próximo frame)
				noChao = false;
			}

			else if (id_jogador == 2)
			{
				if (!noChao)
					vel.y += GRAVIDADE;

				bool moveEsq = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
				bool moveDir = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

				if (moveEsq && !moveDir) {
					vel.x = -VELOCIDADE * speedModifier;
					if (direita)
					{
						corpo.setTexture(pGG->carregar_texturas("./assets/jogador2-esquerda.png"));
						direita = false;
					}
				}
				else if (moveDir && !moveEsq) {
					vel.x = VELOCIDADE * speedModifier;
					if (!direita)
					{
						corpo.setTexture(pGG->carregar_texturas("./assets/jogador2.png"));
						direita = true;
					}
				}
				else
				{
					vel.x = 0.f;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && noChao)
				{
					vel.y -= 6.0;
					noChao = false;
				}
				corpo.move(vel.x, vel.y);

				noChao = false;
			}
		}

		void Jogador::colidir(Entidade* outra, std::string direcao)
		{
			int indice = outra->get_id();
			switch (indice)
			{
			case 1:
				if (direcao == "Acima")
				{
					vel.y = 40 * VELOCIDADE;
					outra->set_vel(sf::Vector2f(outra->get_vel().x, -5 * VELOCIDADE));
				}
				else if (direcao == "Abaixo")
				{
					parado = true;
					vel.y *= -1;
					outra->set_vel(sf::Vector2f(outra->get_vel().x, 5 * VELOCIDADE));
				}
				else if (direcao == "Esquerda")
				{
					vel = sf::Vector2f(10 * VELOCIDADE, vel.y);
					outra->set_vel(sf::Vector2f(-5 * VELOCIDADE, outra->get_vel().y));
				}
				else if (direcao == "Direita")
				{
					vel = sf::Vector2f(-10 * VELOCIDADE, vel.y);
					outra->set_vel(sf::Vector2f(5 * VELOCIDADE, outra->get_vel().y));
				}
				mover();
				break;
			case 11:
				if (direcao == "Abaixo")
				{
					vel = sf::Vector2f(vel.x, 0.f);
				}
				else if (direcao == "Acima")
				{
					vel = sf::Vector2f(vel.x, 0.f);
				}
				else if (direcao == "Esquerda")
				{
					vel = sf::Vector2f(vel.x, vel.y);

				}
				else if (direcao == "Direita")
				{
					vel = sf::Vector2f(vel.x, vel.y);
				}
				break;
			case 12:

				if (direcao == "Abaixo")
				{
					vel = sf::Vector2f(vel.x, 0.f);
				}
				else if (direcao == "Acima")
				{
					vel = sf::Vector2f(vel.x, 0.f);
				}
				else if (direcao == "Esquerda")
				{
					vel = sf::Vector2f(vel.x, vel.y);

				}
				else if (direcao == "Direita")
				{
					vel = sf::Vector2f(vel.x, vel.y);
				}
				break;
			case 13:
				if (direcao == "Abaixo")
				{
					vel = sf::Vector2f(vel.x, -5.f);
				}
				else if (direcao == "Acima")
				{
					vel = sf::Vector2f(vel.x, 5.f);
				}
				else if (direcao == "Esquerda")
				{
					vel = sf::Vector2f(5.f, vel.y);

				}
				else if (direcao == "Direita")
				{
					vel = sf::Vector2f(-5.f, vel.y);
				}
				mover();
				break;
			}
		}

		void Jogador::ataque()
		{
			if ((id_jogador == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) ||
				(id_jogador == 2 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)))
			{
				return;
			}
			dano_ataque = DMG;
			atacando = true;

			if (delay_ataque <= 0)
			{
				delay_ataque = DELAY_ATAQUE;
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
					else
					{
						if (vel.x >= 0)
						{
							direcao = "Direita";
							ataque_direcao = "Direita";
						}
						else
						{
							direcao = "Esquerda";
							ataque_direcao = "Esquerda";
						}
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
					else
					{
						if (vel.x >= 0)
						{
							direcao = "Direita";
							ataque_direcao = "Direita";
						}
						else
						{
							direcao = "Esquerda";
							ataque_direcao = "Esquerda";
						}
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
				gColisoes->colidir_ataque(static_cast<Jogador*>(this), direcao);

			}
			dano_ataque = 0;
		}

		void Jogador::colidir_ataque(Entidade* outra, std::string direcao)
		{
			outra->infligir_dano(dano_ataque);
			if (direcao == "Esquerda")
				vel = sf::Vector2f(RECUO, vel.y);
			else if (direcao == "Direita")
				vel = sf::Vector2f(-RECUO, vel.y);
			else if (direcao == "Acima")
				vel = sf::Vector2f(vel.x, RECUO);
			else if (direcao == "Abaixo")
			{
				vel.y = -10.f;
			}
		}
		void Jogador::salvar(std::ofstream& arquivo)
		{
			if (!arquivo.is_open())
			{
				std::cout << "Erro ao salvar o ARQ jogador" << std::endl;
				return;
			}
			if (vivo)
			{
				arquivo << 1 << std::endl;
			}
			else
			{
				arquivo << 0 << std::endl;
				arquivo << n_vidas << std::endl
					<< corpo.getPosition().x << std::endl
					<< corpo.getPosition().y << std::endl
					<< vel.x << std::endl
					<< vel.y << std::endl
					<< corpo.getSize().x << std::endl
					<< corpo.getSize().y << std::endl;

			}
		}

		void Jogador::aplicar_lentidao(float factor, int duracaoFrames)
		{
			if (factor <= 0.f) return;
			speedModifier = 1.0f / factor;
			if (speedModifier < 0.05f) speedModifier = 0.05f; // limite mínimo
			if (duracaoFrames <= 0) duracaoFrames = 120;
			slowTimer = duracaoFrames;
		}

	}
}