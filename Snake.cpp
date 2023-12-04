//
// Created by 97250 on 25/11/2023.
//

#include <iostream>
#include "Snake.hpp"

Snake::Snake() : m_body(std::list<sf::Sprite>(3)), m_assetManager(AssetManager::getInstance()), m_isDead(false) {
}

void Snake::Init() {
    float offset = 32.f;

    for (auto &segment: m_body) {
        segment.setTexture(m_assetManager.getTexture(Asset::SnakeBody));
        segment.setPosition(offset, 32.f);
        offset += 32.f;
    }

    m_head.setTexture(m_assetManager.getTexture(Asset::SnakeHead));
    m_head.setPosition(offset, 32.f);
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &bodyPart: m_body) {
        target.draw(bodyPart);
    }

    target.draw(m_head);
}

void Snake::Move(const sf::Vector2f direction) {
    if (m_isDead) {
        return;
    }

    sf::Vector2f previousPosition = m_head.getPosition();

    sf::Vector2f newPosition = previousPosition + direction;

    for (auto &segment: m_body) {
        sf::Vector2f currentPosition = segment.getPosition();
        segment.setPosition(previousPosition);
        previousPosition = currentPosition;
    }
    m_head.setPosition(newPosition);
}

bool Snake::Collision(const sf::Sprite &other) const {
    return other.getGlobalBounds().intersects(m_head.getGlobalBounds());
}

bool Snake::FoodCollision(const sf::Sprite &food) const {
    sf::FloatRect headBounds = m_head.getGlobalBounds();
    sf::FloatRect otherBounds = food.getGlobalBounds();

    // Define the shrink factor (e.g., 0.8 for 80% of the original size)
    float shrinkFactor = 0.5f;

    // Shrink the headBounds
    headBounds.left += headBounds.width * (1 - shrinkFactor) / 2;
    headBounds.top += headBounds.height * (1 - shrinkFactor) / 2;
    headBounds.width *= shrinkFactor;
    headBounds.height *= shrinkFactor;

    // Shrink the otherBounds in the same way
    otherBounds.left += otherBounds.width * (1 - shrinkFactor) / 2;
    otherBounds.top += otherBounds.height * (1 - shrinkFactor) / 2;
    otherBounds.width *= shrinkFactor;
    otherBounds.height *= shrinkFactor;

    // Check if the shrunken bounds intersect
    return headBounds.intersects(otherBounds);

}

void Snake::die() {
    m_head.setTexture(m_assetManager.getTexture(Asset::DeadHead));
    m_isDead = true;
}

void Snake::grow(sf::Vector2f position) {
    sf::Sprite segment;
    segment.setTexture(m_assetManager.getTexture(Asset::SnakeBody));
    segment.setPosition(position);

    m_body.push_back(segment);
}


sf::Sprite &Snake::getTail() {
    return m_body.back();
}
