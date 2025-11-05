#pragma once

#include <SFML/Graphics.hpp>
//#include "../entities/Player.h"
//#include "../entities/Enemy.h"
//#include "../entities/Boss.h"
//#include "../entities/Obstacle.h"
#include "../include/ListaEntidades.h"




namespace Gerenciadores
{
	class GerenciadorColisoes
    {
    private:
        //Listas::ListaEntidades* lista_Inimigos;
        Listas::ListaEntidades* lista_Jogadores;
        //Listas::ListaEntidades* lista_Obstaculos;

        const bool tratar_colisao(Entidades::Entidade* A, Entidades::Entidade* B);
    public:
        GerenciadorColisoes();
        ~GerenciadorColisoes();

        void set_ListaInimigos(Listas::ListaEntidades* list) { if (list) { lista_Jogadores = list; } }
        //void set_ListaJogadores(Listas::ListaEntidades* list) { if (list) { lista_Inimigos = list; } }
        //void set_ListaObstaculos(Listas::ListaEntidades* list) { if (list) { lista_Obstaculos = list; } }

        void colide();
        
  
    };
}