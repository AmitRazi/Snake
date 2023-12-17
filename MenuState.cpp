//
// Created by 97250 on 17/12/2023.
//

#include "MenuState.hpp"
#include "Game.hpp"

MenuState::MenuState(std::shared_ptr<Game> game) : GameState(std::move(game)), m_exitMarked(false), m_exitPressed(false), m_playPressed(false),
                                                   m_playMarked(true) {
    sf::Vector2u windowSize = getGame()->getWindowSize();
    m_playText.setFont(m_assetManager.getFont(Asset::Font));
    m_playText.setFillColor(sf::Color::Green);
    AssetManager::centerOrigin(m_playText);
    m_playText.setPosition(windowSize.x / 2.0f - 50.f, windowSize.y / 2.0f - 40.f);

    m_exitText.setFont(m_assetManager.getFont(Asset::Font));
    m_exitText.setFillColor(sf::Color::White);
    AssetManager::centerOrigin(m_exitText);
    m_exitText.setPosition(windowSize.x / 2.0f - 50.f, windowSize.y / 2.0f + 20.f);
    m_playText.setString("Play");
    m_exitText.setString("Exit");
}

void MenuState::pressButton(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Up || key == sf::Keyboard::Down) {
        m_playMarked = !m_playMarked;
        m_exitMarked = !m_exitMarked;
    }

    if (key == sf::Keyboard::Enter) {
        if (m_exitMarked) {
            m_exitPressed = true;
            m_exitMarked = false;
        }

        if (m_playMarked) {
            m_playMarked = false;
            m_playPressed = true;
        }
    }
}


void MenuState::update(sf::Time delta) {
    static sf::Time buffer = sf::Time::Zero;
    buffer += delta;

    if (m_playMarked) {
        m_playText.setFillColor(sf::Color::Green);
        m_exitText.setFillColor(sf::Color::White);
    }

    if (m_exitMarked) {
        m_exitText.setFillColor(sf::Color::Green);
        m_playText.setFillColor(sf::Color::White);
    }

    if (m_exitPressed) {
        getGame()->close();
    }

    if (m_playPressed) {
        getGame()->changeGameState(GameState::Play);
    }
}

void MenuState::draw(sf::RenderWindow &window) {
    window.draw(m_playText);
    window.draw(m_exitText);
}
