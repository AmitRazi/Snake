//
// Created by 97250 on 02/12/2023.
//

#include "AssetManager.hpp"

AssetManager::AssetManager() {
    addTexture(Asset::HorizontalBlock, "C:\\Users\\97250\\Snake\\assets\\wall_block_32_2.png", false);
    addTexture(Asset::HorizontalLeftEdge, "C:\\Users\\97250\\Snake\\assets\\wall_block_32_1.png", false);
    addTexture(Asset::HorizontalRightEdge, "C:\\Users\\97250\\Snake\\assets\\wall_block_32_3.png", false);
    addTexture(Asset::VerticalBlock, "C:\\Users\\97250\\Snake\\assets\\wall_block_32_4.png", false);
    addTexture(Asset::VerticalBottomEdge, "C:\\Users\\97250\\Snake\\assets\\wall_block_32_5.png", false);
    addTexture(Asset::VerticalUpperEdge, "C:\\Users\\97250\\Snake\\assets\\wall_block_32_6.png", false);
    addTexture(Asset::singleBlock, "C:\\Users\\97250\\Snake\\assets\\wall_block_32_0.png", false);
    addTexture(Asset::SnakeBody, "C:\\Users\\97250\\Snake\\assets\\snake_green_blob_32.png", false);
    addTexture(Asset::SnakeHead, "C:\\Users\\97250\\Snake\\assets\\snake_green_head_32.png", false);
    addTexture(Asset::DeadHead, "C:\\Users\\97250\\Snake\\assets\\snake_green_xx_32.png", false);
    addTexture(Asset::Food, "C:\\Users\\97250\\Snake\\assets\\apple_red_32.png", false);
    addTexture(Asset::Logo, "C:\\Users\\97250\\Snake\\assets\\logo2.png", false);
    addTexture(Asset::Food, "C:\\Users\\97250\\Snake\\assets\\apple_red_32.png", false);

    addFont(Asset::Font, "C:\\Users\\97250\\Snake\\assets\\font.ttf");
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