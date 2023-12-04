//
// Created by 97250 on 25/11/2023.
//

#include <Window/Event.hpp>
#include <iostream>
#include "Game.hpp"
Game::Game() :m_window(sf::VideoMode(576,576),"PacSnake"){
    m_gameStates[GameState::Welcome] = new WelcomeState(this);
    m_gameStates[GameState::Menu] = new MenuState(this);
    m_gameStates[GameState::Play] = new PlayState(this);
    m_gameStates[GameState::GameOverState] = new GameOverState(this);


    changeGameState(GameState::Welcome);
}

Game::~Game(){
    for(GameState* state: m_gameStates)
        delete state;
}

void Game::changeGameState(GameState::State gameState) {
    m_currentState = m_gameStates[gameState];
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