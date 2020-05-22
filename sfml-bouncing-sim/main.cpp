#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bouncy!");
    Game game(window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {
        game.run(window);
    }

    return 0;
}