//
// Created by 97250 on 25/11/2023.
//

#include <iostream>
#include "Snake.hpp"

template<typename T>
void centerOrigin(T &drawable) {
    sf::FloatRect bound = drawable.getLocalBounds();
    drawable.setOrigin(bound.width / 2, bound.height / 2);
}

Snake::Snake() : m_body(), m_assetManager(AssetManager::getInstance()){
}

void Snake::Init(int initialSize) {
    m_body.clear();

    float offset = 50.f * initialSize;
    auto head = std::make_unique<bodySegment>();

    head->m_sprite.setTexture(m_assetManager.getTexture(Asset::SnakeHead));
    centerOrigin(head->m_sprite);
    head->m_sprite.setScale(0.8f, 0.8f);
    head->m_sprite.setPosition(offset, 50.f);
    head->m_previousDirection = Direction::Right;
    head->m_currentDirection = Direction::Right;
    m_body.push_back(std::move(head));

    for (int i = 0; i < initialSize; ++i) {
        auto segment = std::make_unique<bodySegment>();
        segment->m_sprite.setTexture(m_assetManager.getTexture(Asset::SnakeBody));
        segment->m_sprite.setScale(0.8f, 0.8f);
        segment->m_currentDirection = Direction::Right;
        segment->m_previousDirection = Direction::Right;
        centerOrigin(segment->m_sprite);

        offset -= 32.f;
        segment->m_sprite.setPosition(offset, 50.f);
        m_body.push_back(std::move(segment));
    }
}


void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &bodyPart: m_body) {
        target.draw(bodyPart->m_sprite);
    }
}

void Snake::move(const Direction direction) {
    // Process the head first
    m_body.front()->m_previousDirection = m_body.front()->m_currentDirection;
    m_body.front()->m_currentDirection = direction;
    m_body.front()->m_sprite.setRotation(getRotationForDirection(direction));

    // Store the previous position of the head to set it to the next segment
    sf::Vector2f previousPosition = m_body.front()->m_sprite.getPosition();
    Direction currentDirection = m_body.front()->m_previousDirection;
    m_body.front()->m_sprite.setPosition(getNewPosition(previousPosition, direction));

    // Now process the rest of the body
    auto currentSegment = std::next(m_body.begin());
    auto previousSegment = m_body.begin();
    while (currentSegment != m_body.end()) {

        // Store the current position of the segment
        sf::Vector2f currentPosition = (*currentSegment)->m_sprite.getPosition();

        // Move this segment to the position where the previous segment was
        (*currentSegment)->m_sprite.setPosition(previousPosition);
        (*currentSegment)->m_sprite.setRotation(getRotationForDirection(currentDirection));
        (*currentSegment)->m_previousDirection = (*currentSegment)->m_currentDirection;
        (*currentSegment)->m_currentDirection = currentDirection;
        currentDirection = (*currentSegment)->m_previousDirection;

        if ((*currentSegment)->m_currentDirection != (*previousSegment)->m_currentDirection) {
            changeToTurning(currentSegment, (*previousSegment)->m_currentDirection);
        } else{
            revertToNormalSprite(currentSegment->get()->m_sprite,currentSegment->get()->m_currentDirection);
        }

        previousSegment = currentSegment;

        // Update previousPosition for the next segment
        previousPosition = currentPosition;
        // Move to the next segment
        ++currentSegment;
    }
}


bool Snake::Collision(const sf::Sprite &other) const {
    return other.getGlobalBounds().intersects(m_body.front()->m_sprite.getGlobalBounds());
}

bool Snake::FoodCollision(const sf::Sprite &food) const {
    sf::FloatRect headBounds = m_body.front()->m_sprite.getGlobalBounds();
    sf::FloatRect otherBounds = food.getGlobalBounds();

    // Define the shrink factor (e.g., 0.8 for 80% of the original size)
    float shrinkFactor = 0.99f;

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

void Snake::grow(sf::Vector2f position) {
    auto segment = std::make_unique<bodySegment>();
    segment->m_sprite.setTexture(m_assetManager.getTexture(Asset::SnakeBody));
    segment->m_sprite.setPosition(position);
    segment->m_sprite.setScale(0.8f, 0.8f);
    segment->m_currentDirection = m_body.back()->m_currentDirection;
    centerOrigin(segment->m_sprite);

    m_body.push_back(std::move(segment));
}


sf::Sprite &Snake::getTail() {
    return m_body.back()->m_sprite;
}

float Snake::getRotationForDirection(Direction direction) {
    switch (direction) {
        case Direction::Up:
            return -90.f;
        case Direction::Down:
            return 90.f;
        case Direction::Left:
            return 180.f;
        default:
            return 0.f;
    }
}

sf::Vector2f Snake::getNewPosition(sf::Vector2f currentPosition, Direction direction) {
    switch (direction) {
        case Direction::Up:
            return currentPosition + sf::Vector2f(0.f, -32.f);
        case Direction::Down:
            return currentPosition + sf::Vector2f(0.f, 32.f);
        case Direction::Left:
            return currentPosition + sf::Vector2f(-32.f, 0.f);
        case Direction::Right:
            return currentPosition + sf::Vector2f(32.f, 0.f);
        default:
            return currentPosition;
    }
}

bool Snake::selfCollision() const {
    auto it = std::next(m_body.begin());

    while (it != m_body.end()) {
        if (m_body.front()->m_sprite.getGlobalBounds().intersects((*it)->m_sprite.getGlobalBounds())) {
            return true;
        }
        it++;
    }
    return false;
}

void Snake::changeToTurning(std::_List_iterator<std::unique_ptr<bodySegment>> segment, Direction previousDirection) {
    (*segment)->m_sprite.setTexture(m_assetManager.getTexture(Asset::TurnBody));
    (*segment)->m_sprite.setScale(0.8f, 0.8f);

    // Determine the rotation based on the combination of previous and current directions
    if ((*segment)->m_currentDirection == Direction::Right) {
        if (previousDirection == Direction::Up) {
            (*segment)->m_sprite.setRotation(0.f);  // Turn from Up to Right
        } else if (previousDirection == Direction::Down) {
            (*segment)->m_sprite.setRotation(270.f);    // Turn from Down to Right
        }
    } else if ((*segment)->m_currentDirection == Direction::Left) {
        if (previousDirection == Direction::Up) {
            (*segment)->m_sprite.setRotation(90.f);   // Turn from Up to Left
        } else if (previousDirection == Direction::Down) {
            (*segment)->m_sprite.setRotation(180.f);  // Turn from Down to Left
        }
    } else if ((*segment)->m_currentDirection == Direction::Up) {
        if (previousDirection == Direction::Right) {
            (*segment)->m_sprite.setRotation(180.f);    // Turn from Right to Up
        } else if (previousDirection == Direction::Left) {
            (*segment)->m_sprite.setRotation(270.f);  // Turn from Left to Up
        }
    } else if ((*segment)->m_currentDirection == Direction::Down) {
        if (previousDirection == Direction::Right) {
            (*segment)->m_sprite.setRotation(90.f);   // Turn from Right to Down
        } else if (previousDirection == Direction::Left) {
            (*segment)->m_sprite.setRotation(0.f);  // Turn from Left to Down
        }
    }

    // Adjust the origin if necessary
    centerOrigin((*segment)->m_sprite);
}

void Snake::revertToNormalSprite(sf::Sprite& sprite, Direction direction) {
    sprite.setTexture(m_assetManager.getTexture(Asset::SnakeBody));
    sprite.setScale(0.8f,0.8f);
    sprite.setRotation(getRotationForDirection(direction));
    centerOrigin(sprite);
}
