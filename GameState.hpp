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

    GameState(Game* game);
    Game* getGame() const;

    virtual void pressButton(sf::Keyboard::Key key) = 0;
    virtual void update(sf::Time delta) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

private:
    Game* m_game;
};

class WelcomeState : public GameState {
    sf::Text m_text;
    sf::Sprite m_sprite;

    bool m_flash;

public:
    WelcomeState(Game* game);

    void pressButton(sf::Keyboard::Key key);
    void update(sf::Time delta);
    void draw(sf::RenderWindow& window);

};

class PlayState : public GameState {
    Snake m_snake;
    Level m_level;

    sf::Vector2f m_snakeDirection;
    sf::Time m_elapsed;

public:
    PlayState(Game* game);

    void pressButton(sf::Keyboard::Key key);
    void update(sf::Time delta);
    void draw(sf::RenderWindow& window);
    void reset();
};

class MenuState : public GameState {
    sf::Text m_playText;
    sf::Text m_exitText;

    bool m_playMarked;
    bool m_playPressed;
    bool m_exitMarked;
    bool m_exitPressed;

public:
    MenuState(Game* game);

    void pressButton(sf::Keyboard::Key key);
    void update(sf::Time delta);
    void draw(sf::RenderWindow& window);

};

class GameOverState : public GameState {
    sf::Text m_gameOverText;
    sf::Text m_replayText;
    sf::Text m_exitText;


    bool m_replayMarked;
    bool m_replayPressed;
    bool m_exitMarked;
    bool m_exitPressed;

public:
    GameOverState(Game* game);

    void pressButton(sf::Keyboard::Key key);
    void update(sf::Time delta);
    void draw(sf::RenderWindow& window);

};



#endif //SNAKE_GAMESTATE_HPP
