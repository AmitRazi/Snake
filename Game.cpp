//
// Created by 97250 on 25/11/2023.
//

#include <Window/Event.hpp>
#include "Game.hpp"
#include "GameOverState.hpp"
#include "WelcomeState.hpp"
#include "MenuState.hpp"
#include "PlayState.hpp"

Game::Game() :m_window(sf::VideoMode(576,576),"PacSnake"){
}

void Game::initialize() {
    auto self = shared_from_this();

    m_gameStates[GameState::Welcome] = std::make_unique<WelcomeState>(self);
    m_gameStates[GameState::Menu] = std::make_unique<MenuState>(self);
    m_gameStates[GameState::Play] = std::make_unique<PlayState>(self);
    m_gameStates[GameState::GameOverState] = std::make_unique<GameOverState>(self);

    changeGameState(GameState::Welcome);
}


Game::~Game(){
}

void Game::changeGameState(GameState::State gameState) {
    m_currentState = m_gameStates[gameState].get();
}


void Game::run() {
    sf::Clock frameClock;
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if (event.type == sf::Event::KeyPressed) {
                    m_currentState->pressButton(event.key.code);
            }
        }
        m_currentState->update(frameClock.restart());
        m_window.clear();
        m_currentState->draw(m_window);
        m_window.display();
    }
}
sf::Vector2u Game::getWindowSize() const{
    return m_window.getSize();
}

void Game::close(){
    m_window.close();
}
