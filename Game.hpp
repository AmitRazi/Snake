//
// Created by 97250 on 25/11/2023.
//

#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP


#include <Graphics/Font.hpp>
#include <Graphics/RenderWindow.hpp>
#include "GameState.hpp"


class Game {
public:

    Game();
    ~Game();

    void run();
    void close();

    void changeGameState(GameState::State gameState);

    sf::Vector2u getWindowSize() const;

private:


    sf::RenderWindow m_window;
    GameState* m_currentState;
    std::array<GameState*,GameState::Count> m_gameStates;
};


#endif //SNAKE_GAME_HPP
