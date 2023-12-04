//
// Created by 97250 on 26/11/2023.
//

#include <Graphics/RectangleShape.hpp>
#include <Graphics/Sprite.hpp>
#include <iostream>
#include <random>
#include <chrono>
#include "Level.hpp"
#include "Game.hpp"

Level::Level(Game *game) : m_game(game), m_assetManager(AssetManager::getInstance()),m_food(m_assetManager.getTexture(Food)) {
}

void Level::loadLevel(std::string name) {
    sf::Image levelData;
    if (!levelData.loadFromFile("C:\\Users\\97250\\Snake\\assets\\small.png")) {
        throw std::runtime_error("Could not load the level");
    }

    auto m_levelSize = levelData.getSize();

    for (int y = 0; y < m_levelSize.y; y++) {
        for (int x = 0; x < m_levelSize.x; x++) {
            sf::Color cellData = levelData.getPixel(x, y);

            if (cellData == sf::Color::Black) {
                m_levelData[x][y] = Wall;
            } else if (cellData == sf::Color::White) {
                m_levelData[x][y] = Empty;
            } else if (cellData == sf::Color::Green) {
                m_levelData[x][y] = Empty;
            } else if (cellData == sf::Color::Blue) {
                m_levelData[x][y] = Empty;
            } else if (cellData == sf::Color::Red) {
                m_levelData[x][y] = Empty;
            } else {
                m_levelData[x][y] = Empty;
            }
        }
    }

    std::cout << m_levelSize.x << " " << m_levelSize.y;
    m_renderTexture.create(32 * m_levelSize.x, 32 * m_levelSize.y);
    m_renderTexture.clear(sf::Color::Green);

    sf::Sprite wallSprite(m_assetManager.getTexture(Asset::HorizontalBlock));

    for (int y = 0; y < m_levelSize.y; y++) {
        for (int x = 0; x < m_levelSize.x; x++) {
            if (m_levelData[x][y] == Wall) {
                wallSprite.setPosition(32 * x, 32 * y);
                m_walls.emplace_back(wallSprite);
                m_renderTexture.draw(wallSprite);
            }
        }
    }
}


void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sf::Sprite(m_renderTexture.getTexture()), states);
}

const std::vector<sf::Sprite> &Level::getWalls() const {
    return m_walls;
}

std::vector<std::pair<int, int>> Level::getEmptyCells() const {
    std::vector<std::pair<int, int>> emptyCells;

    for (int x = 1; x < 17; ++x) {
        for (int y = 1; y < 17; ++y) {
            bool isWall = false;
            for (const auto& wall : m_walls) {
                if (wall.getPosition() == sf::Vector2f(32 * x, 32 * y)) {
                    isWall = true;
                    break;
                }
            }
            if (!isWall) {
                emptyCells.emplace_back(x, y);
            }
        }
    }

    return emptyCells;
}


void Level::placeFoodRandomly() {
    auto emptyCells = getEmptyCells();

    if (emptyCells.empty()) {
        // No empty space left to place food
        return;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 eng(seed);

    std::uniform_int_distribution<> distr(0, emptyCells.size() - 1);

    auto [x, y] = emptyCells[distr(eng)];
    m_food.setPosition(32 * x, 32 * y);
    m_renderTexture.clear(sf::Color::Green); // Clear the texture to remove old food position

    // Redraw walls
    for (const auto& wall : m_walls) {
        m_renderTexture.draw(wall);
    }

    // Draw the food in the new position
    m_renderTexture.draw(m_food);

    // Display the updated render texture
    m_renderTexture.display();
}

sf::Sprite& Level::getFood(){
    return m_food;
}


