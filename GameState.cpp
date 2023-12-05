//
// Created by 97250 on 25/11/2023.
//

#include <Window/Keyboard.hpp>
#include <iostream>
#include <System/Sleep.hpp>
#include "GameState.hpp"
#include "Game.hpp"

template<typename T>
void centerOrigin(T &drawable) {
    sf::FloatRect bound = drawable.getLocalBounds();
    drawable.setOrigin(bound.width / 2, bound.height / 2);
}

GameState::GameState(Game *game) : m_game(game), m_assetManager(AssetManager::getInstance()) {};

WelcomeState::WelcomeState(Game *game) : GameState(game) {
    sf::Vector2u windowSize = game->getWindowSize();

    m_sprite.setTexture(m_assetManager.getTexture(Asset::Logo));
    centerOrigin(m_sprite);
    m_sprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f - 50);

    m_text.setFont(m_assetManager.getFont(Asset::Font));
    m_text.setString("Press Enter to start!");
    m_text.setFillColor(sf::Color::White);
    centerOrigin(m_text);
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

PlayState::PlayState(Game *game) : GameState(game), m_level(game), m_snakeDirection(Direction::Right),
                                   m_elapsed(sf::Time::Zero) {
    reset();
}

void PlayState::pressButton(sf::Keyboard::Key key) {
    Direction newDirection = m_snakeDirection; // Temporary variable to store the new direction

    switch (key) {
        case sf::Keyboard::Up:
            newDirection = Direction::Up;
            break;
        case sf::Keyboard::Down:
            newDirection = Direction::Down;
            break;
        case sf::Keyboard::Left:
            newDirection = Direction::Left;
            break;
        case sf::Keyboard::Right:
            newDirection = Direction::Right;
            break;
        default:
            return; // If it's not a direction key, do nothing
    }

    // Use modulo operation to check for opposite direction
    if ((newDirection % 2) != (m_snakeDirection % 2)) {
        m_snakeDirection = newDirection; // Update the direction if it's not opposite
    }
}

void PlayState::update(sf::Time delta) {
    auto food = m_level.getFood();
    m_elapsed += delta;
    if (m_elapsed.asSeconds() > 0.2) {
        auto walls = m_level.getWalls();
        for (auto wall: walls) {
            if (m_snake.Collision(wall)) {
                reset();
                getGame()->changeGameState(GameOverState);
                return;
            }
        }

        if(m_snake.selfCollision()){
            reset();
            getGame()->changeGameState(GameOverState);
            return;
        }

        if (m_snake.FoodCollision(food)) {
            m_level.placeFoodRandomly();
            auto tailPosition = m_snake.getTail().getPosition();
            m_snake.grow(tailPosition);
        }
        m_snake.move(m_snakeDirection);
        m_elapsed = sf::Time::Zero;
    }
}

void PlayState::reset() {
    m_snakeDirection = Direction::Right;  // Reset direction
    m_elapsed = sf::Time::Zero;
    m_level.loadLevel("small2.png");  // Reload the level
    m_level.placeFoodRandomly();
    m_snake.Init(3);  // Reinitialize the snake

}


void PlayState::draw(sf::RenderWindow &window) {
    window.clear();
    window.draw(m_level);
    window.draw(m_snake);
}

MenuState::MenuState(Game *game) : GameState(game), m_exitMarked(false), m_exitPressed(false), m_playPressed(false),
                                   m_playMarked(true) {
    sf::Vector2u windowSize = game->getWindowSize();
    m_playText.setFont(m_assetManager.getFont(Asset::Font));
    m_playText.setFillColor(sf::Color::Green);
    centerOrigin(m_playText);
    m_playText.setPosition(windowSize.x / 2.0f - 50.f, windowSize.y / 2.0f - 40.f);

    m_exitText.setFont(m_assetManager.getFont(Asset::Font));
    m_exitText.setFillColor(sf::Color::White);
    centerOrigin(m_exitText);
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

Game *GameState::getGame() const {
    return m_game;
}


GameOverState::GameOverState(Game *game) : GameState(game) {
    sf::Vector2u windowSize = game->getWindowSize();

    // Setup GameOver Text
    m_gameOverText.setFont(m_assetManager.getFont(Asset::Font));
    m_gameOverText.setString("Game Over");
    m_gameOverText.setFillColor(sf::Color::Red);
    centerOrigin(m_gameOverText);
    m_gameOverText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f - 100);

    // Setup Replay Text
    m_replayText.setFont(m_assetManager.getFont(Asset::Font));
    m_replayText.setString("Replay");
    m_replayText.setFillColor(sf::Color::White);
    centerOrigin(m_replayText);
    m_replayText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    // Setup Exit Text
    m_exitText.setFont(m_assetManager.getFont(Asset::Font));
    m_exitText.setString("Exit");
    m_exitText.setFillColor(sf::Color::White);
    centerOrigin(m_exitText);
    m_exitText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f + 100);

    m_replayMarked = true;
    m_exitMarked = false;
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