//
// Created by 97250 on 25/11/2023.
//

#ifndef SNAKE_GAMESTATE_HPP
#define SNAKE_GAMESTATE_HPP

#include <System/Vector2.hpp>
#include <Graphics/RenderWindow.hpp>
#include <Graphics/Text.hpp>
#include <Graphics/Sprite.hpp>
#include <Window/Keyboard.hpp>
#include <memory>
#include "Level.hpp"
#include "Snake.hpp"
#include "AssetManager.hpp"

class Game;
class GameState {
public:
    AssetManager& m_assetManager;

    enum State{
        Welcome,
        Menu,
        Play,
        GameOverState,
        Count
    };

    GameState(std::shared_ptr<Game> game);
    virtual ~GameState() {}

    const std::shared_ptr<Game>& getGame() const;
    virtual void pressButton(sf::Keyboard::Key key) = 0;
    virtual void update(sf::Time delta) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

private:
    std::shared_ptr<Game> m_game;
};





#endif //SNAKE_GAMESTATE_HPP
