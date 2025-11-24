#include "../include/ArvoreMonstro.h"
#include "../include/GerenciadorColisoes.h"

#define DELAY 300

namespace Entidades
{
	namespace Personagens
	{

		ArvoreMonstro::ArvoreMonstro(bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, float dmg, sf::Vector2f tam, int delay_ataque) :
			Inimigo(3, pos, velo, tam),
			pProjetil(nullptr),
			delay_ataque(delay_ataque)
		{
			texturas = pGG->carregar_texturas("./assets/Esqueleto.png");
			corpo.setTexture(texturas);
			nivel_maldade = dmg;
			n_vidas = nV;
			vivo = viv;

			// Inicializa pontos de patrulha em torno da posição inicial
			pontoEsquerda = sf::Vector2f(corpo.getPosition().x - LIMITE_PATRULHA, corpo.getPosition().y);
			pontoDireita = sf::Vector2f(corpo.getPosition().x + LIMITE_PATRULHA, corpo.getPosition().y);

			// timers/flags já inicializados por default nos membros
			tempoCooldownTiro = 0.f;
			estaAtacando = false;
			tempoAtaque = 0.6f;
			sentido = 1;
		}
		ArvoreMonstro::~ArvoreMonstro()
		{
			if (pProjetil)
			{
				pProjetil->set_vivo(false);
				pProjetil = nullptr;
			}
		}
		void ArvoreMonstro::executar()
		{
			if (vivo && n_vidas < 0)
				vivo = false;
			delay_ataque--;
			if (delay_ataque < 0)
			{
				atacar();
				delay_ataque = DELAY;
			}
			mover();
		}

		void ArvoreMonstro::mover()
		{
			// Pega posição do jogador (variável estática atualizada pela fase)
			sf::Vector2f posJogador = Entidades::Entidade::posJogador;

			// Posição atual do boss
			sf::Vector2f pos = corpo.getPosition();

			// ====== MOVIMENTO NORMAL / PERSEGUIR JOGADOR ======
			float distancia = std::hypot(posJogador.x - pos.x, posJogador.y - pos.y);

			// Distância de acionamento do boss (ajuste conforme necessário)
			const float DISTANCIA_ATAQUE = 500.f;
			const float PATROL_SPEED = 2.0f; // velocidade de patrulha (pixels por frame)
			const float DT = 1.f / 60.f; // aproximação de delta time simples para timers

			if (distancia < DISTANCIA_ATAQUE)
			{
				perseguindo = true;
				// para mirar / preparar ataque, zera velocidade horizontal de patrulha
				vel.x = 0.f;
				olhandoEsquerda = (posJogador.x < pos.x);

				// dispara se cooldown permitir
				if (delay_ataque <= 0)
				{
					ultimoAlvo = posJogador;
					atacar();
					delay_ataque = DELAY;
				}
			}
			else
			{
				// Patrulha entre dois pontos
				perseguindo = false;
				vel.x = sentido * PATROL_SPEED;
				olhandoEsquerda = (sentido == -1);
			}

			// ====== FÍSICA SIMPLES ======
			// gravidade
			if (!noChao)
				vel.y += GRAVIDADE;
			// atualiza posição
			corpo.move(vel.x, vel.y);

			// atualiza timers
			if (tempoCooldownTiro > 0.f)
				tempoCooldownTiro -= DT;

			if (estaAtacando)
			{
				tempoAtaque -= DT;
				if (tempoAtaque <= 0.f)
				{
					estaAtacando = false;
					tempoAtaque = 0.6f;
				}
			}

			// colisão simples com chão (limite de nível — ajuste conforme seu mapa)
			pos = corpo.getPosition();
			if (pos.y >= 600.f)
			{
				pos.y = 600.f;
				vel.y = 0.f;
				noChao = true;
				corpo.setPosition(pos);
			}
			else
			{
				noChao = false;
			}

			// limites laterais de patrulha
			if (!perseguindo && (pos.x > pontoDireita.x || pos.x < pontoEsquerda.x))
			{
				// refaz sentido e corrige posição para manter dentro da área
				sentido *= -1;
				if (pos.x > pontoDireita.x)
					corpo.setPosition(pontoDireita.x, pos.y);
				else if (pos.x < pontoEsquerda.x)
					corpo.setPosition(pontoEsquerda.x, pos.y);
			}
		}

		void ArvoreMonstro::atacar()
		{
			if (pProjetil && !pProjetil->get_vivo() && tempoCooldownTiro <= 0.f)
			{
				// Configura posição inicial do projétil na "mão" do boss
				sf::Vector2f posInicial = corpo.getPosition();
				if (olhandoEsquerda)
					posInicial.x -= corpo.getSize().x / 2;
				else
					posInicial.x += corpo.getSize().x / 2;
				posInicial.y -= corpo.getSize().y / 4; // ligeiramente acima do centro vertical
				// Calcula direção normalizada para o alvo
				sf::Vector2f direcao = ultimoAlvo - posInicial;
				float comprimento = std::hypot(direcao.x, direcao.y);
				if (comprimento != 0.f)
					direcao /= comprimento; // normaliza
				// Define velocidade do projétil
				const float VELOCIDADE_PROJETIL = 10.f;
				sf::Vector2f velProjetil = direcao * VELOCIDADE_PROJETIL;
				// Ativa o projétil
				pProjetil->set_posicao(posInicial);
				pProjetil->set_vel(velProjetil);
				pProjetil->set_vivo(true);
				// Reseta cooldown
				tempoCooldownTiro = 1.0f; // 1 segundo de cooldown entre tiros
				estaAtacando = true;
			}
		}

		void ArvoreMonstro::colidir(Entidade* outra, std::string direcao)
		{
			int indice = outra->get_id();
			switch (indice)
			{
			case 1:
				// Colisão com jogador
				outra->infligir_dano(nivel_maldade);
				break;
			case 11:
				if (direcao == "Direita" || direcao == "Esquerda")
				{
					vel = sf::Vector2f(-vel.x, vel.y);
				}
				else if (direcao == "Acima" || direcao == "Abaixo")
				{
					vel = sf::Vector2f(vel.x, -vel.y);
				}
				break;
			default:
				break;
			}
		}

		void ArvoreMonstro::desenhar()
		{
			if(vivo)
				pGG->desenhar(&corpo);
		}

		void ArvoreMonstro::salvar(std::ofstream& arquivo)
		{
			if (!arquivo.is_open())
			{
				std::cout << "Erro ao salvar o ARQ ArvoreMonstro" << std::endl;
				return;
			}
			if (vivo)
			{
				arquivo << 3 << std::endl;
				arquivo << 1 << std::endl; // vivo
			}
			else
			{
				arquivo << 3 << std::endl;
				arquivo << 0 << std::endl; // morto
			}
			arquivo << n_vidas << std::endl;
			arquivo << corpo.getPosition().x << " " << corpo.getPosition().y << std::endl;
			arquivo << vel.x << " " << vel.y << std::endl;
			arquivo << nivel_maldade << std::endl;
			arquivo << corpo.getSize().x << " " << corpo.getSize().y << std::endl;
			arquivo << delay_ataque << std::endl;
		}


	}
}