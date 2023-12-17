//
// Created by 97250 on 17/12/2023.
//

#ifndef SNAKE_PLAYSTATE_HPP
#define SNAKE_PLAYSTATE_HPP


#include "GameState.hpp"

class PlayState : public GameState {
    Snake m_snake;
    Level m_level;

    Direction m_snakeDirection;
    sf::Time m_elapsed;

public:
    PlayState(std::shared_ptr<Game> game);

    void pressButton(sf::Keyboard::Key key);

    void draw(sf::RenderWindow& window);
    void update(sf::Time delta);

    void reset();
};



#endif //SNAKE_PLAYSTATE_HPP
