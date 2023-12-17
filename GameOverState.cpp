//
// Created by 97250 on 17/12/2023.
//

#include "GameOverState.hpp"
#include "Game.hpp"

GameOverState::GameOverState(std::shared_ptr<Game> game) : GameState(std::move(game)),m_replayMarked(true),m_exitMarked(false) {
    sf::Vector2u windowSize = getGame()->getWindowSize();

    // Setup GameOver Text
    m_gameOverText.setFont(m_assetManager.getFont(Asset::Font));
    m_gameOverText.setString("Game Over");
    m_gameOverText.setFillColor(sf::Color::Red);
    AssetManager::centerOrigin(m_gameOverText);
    m_gameOverText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f - 100);

    // Setup Replay Text
    m_replayText.setFont(m_assetManager.getFont(Asset::Font));
    m_replayText.setString("Replay");
    m_replayText.setFillColor(sf::Color::White);
    AssetManager::centerOrigin(m_replayText);
    m_replayText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    // Setup Exit Text
    m_exitText.setFont(m_assetManager.getFont(Asset::Font));
    m_exitText.setString("Exit");
    m_exitText.setFillColor(sf::Color::White);
    AssetManager::centerOrigin(m_exitText);
    m_exitText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f + 100);
}

void GameOverState::pressButton(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Up || key == sf::Keyboard::Down) {
        m_replayMarked = !m_replayMarked;
        m_exitMarked = !m_exitMarked;
    }

    if (key == sf::Keyboard::Enter) {
        if (m_replayMarked) {
            m_replayMarked = false;
            m_replayPressed = true;
        }

        if (m_exitMarked) {
            m_exitMarked = false;
            m_exitPressed = true;
        }
    }
}

void GameOverState::update(sf::Time delta) {
    static sf::Time buffer = sf::Time::Zero;
    buffer += delta;

    if (m_replayMarked) {
        m_replayText.setFillColor(sf::Color::Green);
        m_exitText.setFillColor(sf::Color::White);
    }

    if (m_exitMarked) {
        m_exitText.setFillColor(sf::Color::Green);
        m_replayText.setFillColor(sf::Color::White);
    }

    if (m_exitPressed) {
        getGame()->close();
    }

    if (m_replayPressed) {
        m_replayPressed = false;
        m_replayMarked = true;
        getGame()->changeGameState(GameState::Play);
    }
}

void GameOverState::draw(sf::RenderWindow &window) {
    window.draw(m_gameOverText);
    window.draw(m_replayText);
    window.draw(m_exitText);
}