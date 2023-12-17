//
// Created by 97250 on 25/11/2023.
//

#include <Window/Keyboard.hpp>

#include "GameState.hpp"
#include "Game.hpp"


GameState::GameState(std::shared_ptr<Game> game) : m_game(game), m_assetManager(AssetManager::getInstance()) {};

const std::shared_ptr<Game>& GameState::getGame() const {
    return m_game;
}


