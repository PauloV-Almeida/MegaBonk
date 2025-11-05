#include "../stdafx/stdafx.h"
#include "../Jogador.h"
#include "../Inimigo.h"

using namespace Entidades;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 1400), "SFML works!");
    Jogador j(sf::Vector2f(700.0f, 700.0f), sf::Vector2f(0.9f, 0.9f), sf::Vector2f(70.0f, 70.0f));
    Inimigo i(sf::Vector2f(100.0f, 100.0f), sf::Vector2f(0.6f, 0.6f), sf::Vector2f(70.0f, 70.0f));
    i.setJogado(&j);
    Inimigo k(sf::Vector2f(100.0f, 100.0f), sf::Vector2f(0.5f, 0.5f), sf::Vector2f(70.0f, 70.0f));
    k.setJogado(&j);
    k.setColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        j.move();
        i.move();
        k.move();
        window.clear();
        window.draw(j.getCorpo());
        window.draw(i.getCorpo());
        window.draw(k.getCorpo());
        window.display();
    }

    return 0;
}
