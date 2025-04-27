// Character.hpp
#pragma once
#include "Utilities.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Character {
public:
    virtual ~Character() {}
    virtual void init(const Texture& tex) = 0;
    virtual void updateControl(float dt) = 0;      // controlled by player input
    virtual void follow(Character* leader, float dt) = 0; // AI follow behavior
    virtual void render(RenderWindow& win, float offsetX = 0.f) = 0;
};

// Sonic implementation
class Sonic : public Character {
private:
    Sprite sprite;
    float speed{ 200.f };
public:
    void init(const Texture& tex) override {
        sprite.setTexture(tex);
        sprite.setScale(2.0f, 2.0f);
    }
    void updateControl(float dt) override {
        if (Keyboard::isKeyPressed(Keyboard::Left))  sprite.move(-speed * dt, 0);
        if (Keyboard::isKeyPressed(Keyboard::Right)) sprite.move(speed * dt, 0);
        // jump, gravity, etc.
    }
    void follow(Character* leader, float dt) override {
        // simple linear follow: move towards leader x
        // dynamic_cast to get sprite position
        Sonic* lead = dynamic_cast<Sonic*>(leader);
        if (lead) {
            float lx = lead->sprite.getPosition().x;
            float x = sprite.getPosition().x;
            if (abs(lx - x) > 5.f)
                sprite.move((lx > x ? speed : -speed) * dt * 0.5f, 0);
        }
    }
    void render(RenderWindow& win, float offsetX = 0.f) override {
        Vector2f pos = sprite.getPosition();
        sprite.setPosition(pos.x + offsetX, pos.y);
        win.draw(sprite);
        sprite.setPosition(pos);
    }
};

// Tails implementation
class Tails : public Character {
private:
    Sprite sprite;
    float speed{ 150.f };
public:
    void init(const Texture& tex) override {
        sprite.setTexture(tex);
        sprite.setScale(2.0f, 2.0f);
    }
    void updateControl(float dt) override {
        if (Keyboard::isKeyPressed(Keyboard::Left))  sprite.move(-speed * dt, 0);
        if (Keyboard::isKeyPressed(Keyboard::Right)) sprite.move(speed * dt, 0);
        if (Keyboard::isKeyPressed(Keyboard::Up))    sprite.move(0, -speed * dt);
        if (Keyboard::isKeyPressed(Keyboard::Down))  sprite.move(0, speed * dt);
    }
    void follow(Character* leader, float dt) override {
        // hover-follow: move towards leader both axes
        // dynamic_cast to Character with sprite
        // For simplicity, assume leader has getPosition
    }
    void render(RenderWindow& win, float offsetX = 0.f) override {
        Vector2f pos = sprite.getPosition();
        sprite.setPosition(pos.x + offsetX, pos.y);
        win.draw(sprite);
        sprite.setPosition(pos);
    }
};

// Knuckles implementation
class Knuckles : public Character {
private:
    Sprite sprite;
    float speed{ 180.f };
public:
    void init(const Texture& tex) override {
        sprite.setTexture(tex);
        sprite.setScale(2.0f, 2.0f);
    }
    void updateControl(float dt) override {
        if (Keyboard::isKeyPressed(Keyboard::Left))  sprite.move(-speed * dt, 0);
        if (Keyboard::isKeyPressed(Keyboard::Right)) sprite.move(speed * dt, 0);
        // knock/punch input omitted
    }
    void follow(Character* leader, float dt) override {
        // side-by-side follow: maintain offset
    }
    void render(RenderWindow& win, float offsetX = 0.f) override {
        Vector2f pos = sprite.getPosition();
        sprite.setPosition(pos.x + offsetX, pos.y);
        win.draw(sprite);
        sprite.setPosition(pos);
    }
};
