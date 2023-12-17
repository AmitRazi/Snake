//
// Created by 97250 on 02/12/2023.
//

#include <iostream>
#include "AssetManager.hpp"




AssetManager::AssetManager() {
    addTexture(Asset::HorizontalWall, "..\\assets\\wall_block_32_2.png", false);
    addTexture(Asset::LeftEdgeWall, "..\\assets\\wall_block_32_1.png", false);
    addTexture(Asset::RightEdgeWall, "..\\assets\\wall_block_32_3.png", false);
    addTexture(Asset::VerticalWall, "..\\assets\\wall_block_32_5.png", false);
    addTexture(Asset::TopEdgeWall, "..\\assets\\wall_block_32_4.png", false);
    addTexture(Asset::BottomEdgeWall, "..\\assets\\wall_block_32_6.png", false);
    addTexture(Asset::SnakeBody, "..\\assets\\body_horizontal.png", false);
    addTexture(Asset::SnakeHead, "..\\assets\\head_right.png", false);
    addTexture(Asset::VerticalBody, "..\\assets\\body_vertical.png", false);
    addTexture(Asset::TurnBody, "..\\assets\\body_bottomright.png", false);
    addTexture(Asset::Food, "..\\assets\\apple.png", false);
    addTexture(Asset::Logo, "..\\assets\\logo2.png", false);

    addFont(Asset::Font, "..\\assets\\font.ttf");

}
AssetManager& AssetManager::getInstance(){
    static AssetManager manager;
    return manager;
}

void AssetManager::addTexture(Asset assetID, const std::string& filePath, bool isRepeating){
    auto texture = std::make_unique<sf::Texture>();

    if(texture->loadFromFile(filePath)){
        texture->setRepeated(isRepeating);
        m_textures[assetID] = std::move(texture);
    }
}

void AssetManager::addFont(Asset assetID, const std::string& filePath){
    auto font = std::make_unique<sf::Font>();

    if(font->loadFromFile(filePath)){
        m_fonts[assetID] = std::move(font);
    }
}

const sf::Font& AssetManager::getFont(Asset asset){
    return *(m_fonts[asset]);
}

const sf::Texture& AssetManager::getTexture(Asset asset){
    return *(m_textures[asset]);
}

