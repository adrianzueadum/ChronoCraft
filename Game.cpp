#include "Game.hpp"
#include <algorithm>

struct StateSnapshot {
    float time;
    sf::Vector2f position;
    sf::Vector2f velocity;
};

class Player : public Entity {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
    std::vector<StateSnapshot> history;
    float gravity;
    bool isGrounded;

public:
    Player(float x, float y) : position(x, y), velocity(0.f, 0.f), gravity(400.f), isGrounded(false) {
        shape.setSize(sf::Vector2f(20.f, 20.f));
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(position);
    }

    void update(float deltaTime, float timeScale) override {
        if (timeScale >= 0) { // Normal or fast-forward
            velocity.y += gravity * deltaTime * timeScale;
            position += velocity * deltaTime * timeScale;
            if (position.y > 580.f) { // Ground collision
                position.y = 580.f;
                velocity.y = 0.f;
                isGrounded = true;
            }
            shape.setPosition(position);
            if (timeScale == 1.f) { // Record only in normal time
                recordState();
            }
        }
    }

    void render(sf::RenderWindow& window) const override {
        window.draw(shape);
    }

    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }

    void recordState() override {
        history.push_back({currentTime, position, velocity});
        if (history.size() > 1000) { // Limit history
            history.erase(history.begin());
        }
    }

    void rewindTo(float time) override {
        auto it = std::find_if(history.rbegin(), history.rend(),
            [time](const StateSnapshot& s) { return s.time <= time; });
        if (it != history.rend()) {
            position = it->position;
            velocity = it->velocity;
            shape.setPosition(position);
        }
    }
};

class Platform : public Entity {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    std::vector<StateSnapshot> history;
    float moveSpeed;
    float moveRange;
    float baseX;

public:
    Platform(float x, float y, float width, float height, float speed, float range)
        : position(x, y), moveSpeed(speed), moveRange(range), baseX(x) {
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(position);
    }

    void update(float deltaTime, float timeScale) override {
        if (timeScale >= 0) {
            float offset = std::sin(currentTime * moveSpeed) * moveRange;
            position.x = baseX + offset;
            shape.setPosition(position);
            if (timeScale == 1.f) {
                recordState();
            }
        }
    }

    void render(sf::RenderWindow& window) const override {
        window.draw(shape);
    }

    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }

    void recordState() override {
        history.push_back({currentTime, position, sf::Vector2f(0.f, 0.f)});
        if (history.size() > 1000) {
            history.erase(history.begin());
        }
    }

    void rewindTo(float time) override {
        auto it = std::find_if(history.rbegin(), history.rend(),
            [time](const StateSnapshot& s) { return s.time <= time; });
        if (it != history.rend()) {
            position = it->position;
            shape.setPosition(position);
        }
    }
};

Game::Game(sf::RenderWindow& win) : window(win), timeScale(1.f), currentTime(0.f), isPaused(false) {
    player = std::make_unique<Player>(100.f, 300.f);
    entities.push_back(std::make_unique<Platform>(300.f, 500.f, 100.f, 20.f, 2.f, 50.f));
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
                player = std::make_unique<Player>(100.f, 300.f);
                entities.clear();
                entities.push_back(std::make_unique<Platform>(300.f, 500.f, 100.f, 20.f, 2.f, 50.f));
                timeScale = 1.f;
                currentTime = 0.f;
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.key.code == sf::Keyboard::Q) {
                timeScale = -1.f; // Rewind
            } else if (event.key.code == sf::Keyboard::E) {
                timeScale = 2.f; // Fast-forward
            }
        } else if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::E) {
                timeScale = 1.f; // Return to normal
            }
        }
    }

    // Continuous input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player->setPosition(player->getPosition() + sf::Vector2f(-100.f * timeScale, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player->setPosition(player->getPosition() + sf::Vector2f(100.f * timeScale, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (dynamic_cast<Player&>(*player).isGrounded) {
            dynamic_cast<Player&>(*player).applyForce(sf::Vector2f(0.f, -300.f));
            dynamic_cast<Player&>(*player).isGrounded = false;
        }
    }
}

void Game::update(float deltaTime) {
    if (isPaused) return;

    currentTime += deltaTime * timeScale;
    if (currentTime < 0) currentTime = 0;

    if (timeScale < 0) { // Rewind
        player->rewindTo(currentTime);
        for (auto& entity : entities) {
            entity->rewindTo(currentTime);
        }
    } else { // Normal or fast-forward
        player->update(deltaTime, timeScale);
        for (auto& entity : entities) {
            entity->update(deltaTime, timeScale);
        }
    }
}

void Game::render() {
    window.clear(sf::Color::Black);
    player->render(window);
    for (const auto& entity : entities) {
        entity->render(window);
    }
    window.display();
}
