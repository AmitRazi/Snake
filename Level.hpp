//
// Created by 97250 on 26/11/2023.
//

#ifndef SNAKE_LEVEL_HPP
#define SNAKE_LEVEL_HPP


#include <Graphics/Drawable.hpp>
#include <vector>
#include <Graphics/RenderTexture.hpp>
#include <array>
#include <memory>
#include "AssetManager.hpp"

class Game;

class Level : public sf::Drawable {
    enum cellData {
        Empty,
        Wall,
        Fruit
    };

    std::array<std::array<cellData, 18>, 18> m_levelData;
    sf::RenderTexture m_renderTexture;
    std::vector<sf::Sprite> m_walls;
    Game* m_game;
    AssetManager& m_assetManager;
    sf::Sprite m_food;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
    Level(Game *game);

    void loadLevel(std::string name);

    const std::vector<sf::Sprite>& getWalls()const;

    void placeFoodRandomly();

    std::vector<std::pair<int, int>> getEmptyCells() const;

    sf::Sprite& getFood();

    void drawLevel();
    };
#endif //SNAKE_LEVEL_HPP
