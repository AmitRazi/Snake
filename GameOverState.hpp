//
// Created by 97250 on 17/12/2023.
//

#ifndef SNAKE_GAMEOVERSTATE_HPP
#define SNAKE_GAMEOVERSTATE_HPP

#include "GameState.hpp"

class GameOverState : public GameState {
    sf::Text m_gameOverText;
    sf::Text m_replayText;
    sf::Text m_exitText;


    bool m_replayMarked;
    bool m_replayPressed;
    bool m_exitMarked;
    bool m_exitPressed;

public:
    GameOverState(std::shared_ptr<Game> game);

    void pressButton(sf::Keyboard::Key key) override;
    void update(sf::Time delta) override;
    void draw(sf::RenderWindow& window) override;

};



#endif //SNAKE_GAMEOVERSTATE_HPP
