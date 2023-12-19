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
#include <deque>
#include "Level.hpp"

enum Direction {
    Up,
    Right,
    Down,
    Left
};


struct bodySegment{
    sf::Sprite m_sprite;
    Direction m_previousDirection;
    Direction m_currentDirection;
};


class Snake : public sf::Drawable {
private:
    std::list<std::unique_ptr<bodySegment>> m_body;
    AssetManager& m_assetManager;

public:
    Snake();

    void init(int initialSize);

    std::unique_ptr<bodySegment> createSegment(Asset textureAsset, float positionOffset, Direction direction);

    void move(Direction direction);

    void moveBodySegment(bodySegment& currentSegment,
                         Direction& currentDirection);

    void moveTail(const sf::Vector2f& newPosition,const Direction& newDirection);

    bool collision(const sf::Sprite& other,const float shrinkFactor) const;

    bool selfCollision() const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void grow(const sf::Vector2f& position);

    float getRotationForDirection(Direction direction) const;

    sf::Vector2f getNewPosition(const sf::Vector2f& currentPosition, Direction direction) const;

    sf::Sprite& getTail() const;

    void changeToTurning(const std::_List_iterator<std::unique_ptr<bodySegment>>& iterator, Direction direction);

    void revertToNormalSprite(sf::Sprite& sprite, Direction direction);
};


#endif //SNAKE_SNAKE_HPP
