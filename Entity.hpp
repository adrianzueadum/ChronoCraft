#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Graphics.hpp>
#include <vector>

class Entity {
public:
    virtual ~Entity() = default;
    virtual void update(float deltaTime, float timeScale) = 0;
    virtual void render(sf::RenderWindow& window) const = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual void setPosition(const sf::Vector2f& pos) = 0;
    virtual void recordState() = 0;
    virtual void rewindTo(float time) = 0;
};

#endif // ENTITY_HPP
