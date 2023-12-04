//
// Created by 97250 on 25/11/2023.
//

#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP


#include <Graphics/Drawable.hpp>
#include <Graphics/Transformable.hpp>
#include <System/Time.hpp>
#include <Graphics/Sprite.hpp>
#include <list>
#include "Level.hpp"


class Snake : public sf::Drawable {
private:
    sf::Sprite m_head;
    std::list<sf::Sprite> m_body;
    AssetManager& m_assetManager;
    bool m_isDead;

public:
    Snake();

    void Init();

    void Move(const sf::Vector2f direction);

    bool FoodCollision(const sf::Sprite &food) const;

    bool Collision(const sf::Sprite& other) const;

    void Grow();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void die();

    void grow(sf::Vector2f position);

    sf::Sprite& getTail();

    sf::Sprite& getHead(){
        return m_head;
    }


};


#endif //SNAKE_SNAKE_HPP
