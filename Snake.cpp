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

Snake::Snake() : m_body(), m_assetManager(AssetManager::getInstance()) {
}

void Snake::init(int initialSize) {
    m_body.clear();

    float offset = 50.f * static_cast<float>(initialSize);

    // Create head segment
    m_body.push_back(createSegment(Asset::SnakeHead, offset, Direction::Right));

    // Create body segments
    for (int i = 0; i < initialSize - 1; ++i) {
        offset -= 32.f;
        m_body.push_back(createSegment(Asset::SnakeBody, offset, Direction::Right));
    }

    // Create tail segment
    offset -= 32.f;
    m_body.push_back(createSegment(Asset::SnakeTail, offset, Direction::Right));
}

std::unique_ptr<bodySegment> Snake::createSegment(Asset textureAsset, float positionOffset, Direction direction) {
    auto segment = std::make_unique<bodySegment>();
    segment->m_sprite.setTexture(m_assetManager.getTexture(textureAsset));
    centerOrigin(segment->m_sprite);
    segment->m_sprite.setPosition(positionOffset, 50.f);
    segment->m_currentDirection = direction;
    segment->m_previousDirection = direction;

    return segment;
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &bodyPart: m_body) {
        target.draw(bodyPart->m_sprite);
    }
}

void Snake::move(Direction direction) {
    auto &head = m_body.front();

    sf::Vector2f previousPosition = head->m_sprite.getPosition();
    Direction nextDirection = head->m_currentDirection;

    moveBodySegment(*head,direction);

    // Now process the rest of the body
    auto currentSegment = std::next(m_body.begin());
    auto previousSegment = m_body.begin();
    auto endSegment = std::prev(m_body.end());
    while (currentSegment != endSegment) {

        // Store the current position of the segment
        sf::Vector2f currentPosition = (*currentSegment)->m_sprite.getPosition();

        // Move this segment to the position where the previous segment was
        moveBodySegment(*currentSegment->get(),nextDirection);
        nextDirection = (*currentSegment)->m_previousDirection;

        if ((*currentSegment)->m_currentDirection != (*previousSegment)->m_currentDirection) {
            changeToTurning(currentSegment, (*previousSegment)->m_currentDirection);
        } else {
            revertToNormalSprite(currentSegment->get()->m_sprite, currentSegment->get()->m_currentDirection);
        }

        previousSegment = currentSegment;

        // Update previousPosition for the next segment
        previousPosition = currentPosition;
        // Move to the next segment
        ++currentSegment;
    }

    nextDirection = std::prev(endSegment)->get()->m_currentDirection;

// Process the tail segment
    (*endSegment)->m_previousDirection = (*endSegment)->m_currentDirection;
    (*endSegment)->m_currentDirection = nextDirection;
    (*endSegment)->m_sprite.setPosition(getNewPosition((*endSegment)->m_sprite.getPosition(), std::prev(endSegment)->get()->m_previousDirection));
    (*endSegment)->m_sprite.setRotation(getRotationForDirection(nextDirection));

}


void Snake::moveHead(Direction newDirection) {
    auto &head = (*m_body.front());
    head.m_previousDirection = m_body.front()->m_currentDirection;
    head.m_currentDirection = newDirection;
    head.m_sprite.setRotation(getRotationForDirection(newDirection));
    head.m_sprite.setPosition(getNewPosition(head.m_sprite.getPosition(), newDirection));
}

void Snake::moveBodySegment(bodySegment &currentSegment,
                            Direction &nextDirection) {

    currentSegment.m_sprite.setPosition(getNewPosition(currentSegment.m_sprite.getPosition(), nextDirection));
    currentSegment.m_sprite.setRotation(getRotationForDirection(nextDirection));
    currentSegment.m_previousDirection = currentSegment.m_currentDirection;
    currentSegment.m_currentDirection = nextDirection;

}


bool Snake::collision(const sf::Sprite &other) const {
    sf::FloatRect headBounds = m_body.front()->m_sprite.getGlobalBounds();
    sf::FloatRect otherBounds = other.getGlobalBounds();

    // Define the shrink factor (e.g., 0.8 for 80% of the original size)
    float shrinkFactor = 0.50f;

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

bool Snake::foodCollision(const sf::Sprite &food) const {
    sf::FloatRect headBounds = m_body.front()->m_sprite.getGlobalBounds();
    sf::FloatRect otherBounds = food.getGlobalBounds();

    // Define the shrink factor (e.g., 0.8 for 80% of the original size)
    float shrinkFactor = 0.50f;

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

void Snake::grow(const sf::Vector2f &position) {
    auto segment = std::make_unique<bodySegment>();
    segment->m_sprite.setTexture(m_assetManager.getTexture(Asset::SnakeTail));
    segment->m_sprite.setPosition(position);
    segment->m_currentDirection = m_body.back()->m_currentDirection;
    centerOrigin(segment->m_sprite);

    m_body.push_back(std::move(segment));
}


sf::Sprite &Snake::getTail() const {
    return m_body.back()->m_sprite;
}

float Snake::getRotationForDirection(Direction direction) const {
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

sf::Vector2f Snake::getNewPosition(const sf::Vector2f &currentPosition, Direction direction) const {
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

void Snake::changeToTurning(const std::_List_iterator<std::unique_ptr<bodySegment>> &iterator, Direction direction) {
    (*iterator)->m_sprite.setTexture(m_assetManager.getTexture(Asset::TurnBody));
    // Determine the rotation based on the combination of previous and current directions
    if ((*iterator)->m_currentDirection == Direction::Right) {
        if (direction == Direction::Up) {
            (*iterator)->m_sprite.setRotation(0.f);  // Turn from Up to Right
        } else if (direction == Direction::Down) {
            (*iterator)->m_sprite.setRotation(270.f);    // Turn from Down to Right
        }
    } else if ((*iterator)->m_currentDirection == Direction::Left) {
        if (direction == Direction::Up) {
            (*iterator)->m_sprite.setRotation(90.f);   // Turn from Up to Left
        } else if (direction == Direction::Down) {
            (*iterator)->m_sprite.setRotation(180.f);  // Turn from Down to Left
        }
    } else if ((*iterator)->m_currentDirection == Direction::Up) {
        if (direction == Direction::Right) {
            (*iterator)->m_sprite.setRotation(180.f);    // Turn from Right to Up
        } else if (direction == Direction::Left) {
            (*iterator)->m_sprite.setRotation(270.f);  // Turn from Left to Up
        }
    } else if ((*iterator)->m_currentDirection == Direction::Down) {
        if (direction == Direction::Right) {
            (*iterator)->m_sprite.setRotation(90.f);   // Turn from Right to Down
        } else if (direction == Direction::Left) {
            (*iterator)->m_sprite.setRotation(0.f);  // Turn from Left to Down
        }
    }

    // Adjust the origin if necessary
    centerOrigin((*iterator)->m_sprite);
}

void Snake::revertToNormalSprite(sf::Sprite &sprite, Direction direction) {
    sprite.setTexture(m_assetManager.getTexture(Asset::SnakeBody));
    sprite.setRotation(getRotationForDirection(direction));
    centerOrigin(sprite);
}
