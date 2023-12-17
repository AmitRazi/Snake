#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <iostream>

int main()
{
    std::shared_ptr<Game> game = std::make_shared<Game>();
    game->initialize();
    game->run();
}


