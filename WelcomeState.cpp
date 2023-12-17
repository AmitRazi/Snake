//
// Created by 97250 on 17/12/2023.
//

#include "WelcomeState.hpp"
#include "Game.hpp"

WelcomeState::WelcomeState(std::shared_ptr<Game> game) : GameState(game) {
    sf::Vector2u windowSize = game->getWindowSize();

    m_sprite.setTexture(m_assetManager.getTexture(Asset::Logo));
    AssetManager::centerOrigin(m_sprite);
    m_sprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f - 50);

    m_text.setFont(m_assetManager.getFont(Asset::Font));
    m_text.setString("Press Enter to start!");
    m_text.setFillColor(sf::Color::White);
    AssetManager::centerOrigin(m_text);
    m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f + 200);

    m_flash = true;
}

void WelcomeState::pressButton(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Enter)
        getGame()->changeGameState(GameState::Menu);
}


void WelcomeState::update(sf::Time delta) {
    static sf::Time buffer = sf::Time::Zero;
    buffer += delta;

    while (buffer >= sf::seconds(0.25)) {
        m_flash = !m_flash;
        buffer -= sf::seconds(0.5);
    }
}

void WelcomeState::draw(sf::RenderWindow &window) {
    window.draw(m_sprite);

    if (m_flash) {
        window.draw(m_text);
    }
}

