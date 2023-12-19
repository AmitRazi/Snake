//
// Created by 97250 on 02/12/2023.
//

#ifndef SNAKE_ASSETMANAGER_HPP
#define SNAKE_ASSETMANAGER_HPP


#include <Graphics/Font.hpp>
enum Asset{
    Empty,
    LeftEdgeWall,
    RightEdgeWall,
    VerticalWall,
    BottomEdgeWall,
    TopEdgeWall,
    HorizontalWall,
    SnakeHead,
    SnakeBody,
    SnakeTail,
    TurnBody,
    Food,
    Font,
    Logo
};

class AssetManager {
    std::map<Asset,std::unique_ptr<sf::Texture>> m_textures;
    std::map<Asset,std::unique_ptr<sf::Font>> m_fonts;

    AssetManager();
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

public:
    static AssetManager& getInstance();

    template<typename T>
    static void centerOrigin(T &drawable) {
        sf::FloatRect bound = drawable.getLocalBounds();
        drawable.setOrigin(bound.width / 2, bound.height / 2);
    }

    void addTexture(Asset assetID,const std::string& filePath, bool isRepeating);
    void addFont(Asset assetID, const std::string& filePath);

    const sf::Font& getFont(Asset asset);
    const sf::Texture& getTexture(Asset asset);
};


#endif //SNAKE_ASSETMANAGER_HPP
