//
// Created by 97250 on 17/12/2023.
//

#include "PlayState.hpp"
#include "Game.hpp"

PlayState::PlayState(std::shared_ptr<Game> game) : GameState(std::move(game)), m_level(), m_snakeDirection(Direction::Right),
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
            auto tailPosition = m_snake.GetTail().getPosition();
            m_snake.grow(tailPosition);
        }
        m_snake.move(m_snakeDirection);
        m_elapsed = sf::Time::Zero;
    }
}

