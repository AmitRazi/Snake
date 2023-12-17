//
// Created by 97250 on 17/12/2023.
//

#ifndef SNAKE_MENUSTATE_HPP
#define SNAKE_MENUSTATE_HPP

#include "GameState.hpp"

class MenuState : public GameState {
    sf::Text m_playText;
    sf::Text m_exitText;

    bool m_playMarked;
    bool m_playPressed;
    bool m_exitMarked;
    bool m_exitPressed;

public:
    MenuState(std::shared_ptr<Game> game);

    void pressButton(sf::Keyboard::Key key);
    void update(sf::Time delta);
    void draw(sf::RenderWindow& window);

};



#endif //SNAKE_MENUSTATE_HPP
