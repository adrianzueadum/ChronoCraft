#ifndef GAME_HPP
#define GAME_HPP
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Game {
private:
    sf::RenderWindow& window;
    std::vector<std::unique_ptr<Entity>> entities;
    std::unique_ptr<Entity> player;
    float timeScale; // 1.0 = normal, <0 = rewind, >1 = fast-forward
    float currentTime;
    bool isPaused;

public:
    Game(sf::RenderWindow& win);
    void handleEvents();
    void update(float deltaTime);
    void render();
};

#endif // GAME_HPP
