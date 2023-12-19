//
// Created by 97250 on 17/12/2023.
//

#ifndef SNAKE_WELCOMESTATE_HPP
#define SNAKE_WELCOMESTATE_HPP


#include "GameState.hpp"

class WelcomeState : public GameState {
    sf::Text m_text;
    sf::Sprite m_sprite;

    bool m_flash;

public:
    WelcomeState(std::shared_ptr<Game> game);

    void pressButton(sf::Keyboard::Key key);
    void update(sf::Time delta);
    void draw(sf::RenderWindow& window);
};



#endif //SNAKE_WELCOMESTATE_HPP
