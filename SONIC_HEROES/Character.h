   // CharacterPlatform.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Animation.h"
#include <cmath>
#include <iostream>

// ======================== Hitbox ========================
struct Hitbox {
    float width{ 0 }, height{ 0 };
    sf::RectangleShape shape;

    Hitbox() {
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Red);
        shape.setOutlineThickness(1.f);
    }
    Hitbox(float w, float h)
        : width(w), height(h)
    {
        shape.setSize({ w, h });
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Red);
        shape.setOutlineThickness(1.f);
    }

    void setSize(float w, float h) {
        width = w; height = h;
        shape.setSize({ w, h });
    }
    void setPosition(float x, float y) {
        shape.setPosition(x, y);
    }
    float left()   const { return shape.getPosition().x; }
    float top()    const { return shape.getPosition().y; }
    float right()  const { return left() + width; }
    float bottom() const { return top() + height; }
};

// ======================== Platform ========================
class Platform {
public:
    // checks if any tile under the hitbox is 'w'
    static bool checkCollision(const Hitbox& hb, char** grid) {
        int leftCell = int(hb.left() / GameConstants::CELL_SIZE);
        int rightCell = int((hb.right() - 1) / GameConstants::CELL_SIZE);
        int topCell = int(hb.top() / GameConstants::CELL_SIZE);
        int bottomCell = int((hb.bottom() - 1) / GameConstants::CELL_SIZE);

        for (int row = topCell; row <= bottomCell; ++row) {
            if (row < 0 || row >= 14) continue;
            for (int col = leftCell; col <= rightCell; ++col) {
                if (col < 0 || col >= 110) continue;
                if (grid[row][col] == 'w')
                    return true;
            }
        }
        return false;
    }
};

// ======================== Character ========================
class Character {
protected:
    float posX, posY;
    float velocityX, velocityY;
    bool  isOnGround;
    float gravityAcceleration;
    float terminalVelocity;
    float movementSpeed;
    int   spriteWidth, spriteHeight;
    int   hitboxOffsetX, hitboxOffsetY;
    Animation anim;
    Hitbox    hb;

public:
    Character()
        : posX(100.f), posY(100.f),
        velocityX(0.f), velocityY(0.f),
        isOnGround(false),
        gravityAcceleration(0.5f), terminalVelocity(20.f), movementSpeed(5.f),
        spriteWidth(int(40 * 2.5f)), spriteHeight(int(38 * 2.5f)),
        hitboxOffsetX(int(8 * 2.5f)), hitboxOffsetY(int(1.9f * 2.5f)),
        hb(spriteWidth - 2 * hitboxOffsetX, spriteHeight - hitboxOffsetY)
    {
    }

    virtual ~Character() {}

    virtual void handleInput() {
        velocityX = 0.f;
        float speed = movementSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && isOnGround)
            speed *= 2.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocityX = -speed;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocityX = speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isOnGround) {
            velocityY = -20.f;
            isOnGround = false;
        }
    }

    virtual void update(char** levelGrid, bool isControlled, float deltaTime) {
        if (isControlled) handleInput();

        // Horizontal movement & collision
        posX += velocityX;
        if (velocityX != 0.f) {
            float midY = posY + spriteHeight * 0.5f;
            int rowMid = int(midY / GameConstants::CELL_SIZE);
            int colLeft = int((posX + hitboxOffsetX) / GameConstants::CELL_SIZE);
            int colRight = int((posX + spriteWidth - hitboxOffsetX) / GameConstants::CELL_SIZE);
            if (rowMid >= 0 && rowMid < 14) {
                if (velocityX > 0 && levelGrid[rowMid][colRight] == 'w') posX -= velocityX;
                if (velocityX < 0 && levelGrid[rowMid][colLeft] == 'w') posX -= velocityX;
            }
        }

        // Prepare hitbox at next vertical position
        float nextY = posY + velocityY;
        hb.setPosition(posX + hitboxOffsetX, nextY + hitboxOffsetY);

        // Vertical collision via hitbox
        if (Platform::checkCollision(hb, levelGrid)&& velocityY>=0) {
            // landed
            isOnGround = true;
            velocityY = 0.f;

            // snap to top of tile
            int landedRow = int((hb.bottom()) / GameConstants::CELL_SIZE);
            posY = landedRow * GameConstants::CELL_SIZE
                - (spriteHeight - hitboxOffsetY);
        }
        else {
            // in air
            isOnGround = false;
            posY = nextY;
            velocityY += gravityAcceleration;
            if (velocityY > terminalVelocity) velocityY = terminalVelocity;
        }

        // update hitbox to current
        hb.setPosition(posX + hitboxOffsetX, posY + hitboxOffsetY);

        // update animation
        anim.setPosition(posX, posY);
        anim.update(deltaTime);
    }

    int getX() const { return int(posX); }

    virtual void draw(sf::RenderWindow& window, float offsetX) {
        // draw hitbox
        hb.shape.move(-offsetX, 0.f);
        window.draw(hb.shape);
        hb.shape.move(offsetX, 0.f);

        // draw sprite
        anim.draw(window, offsetX);
    }
};

// ======================== Sonic Character ========================
class Sonic : public Character {
private:
    Animation stillL, stillR, walkLeft, walkRight, runLeft, runRight, attackLeft, attackRight;
    Animation* currentAnim;
    Animation* previousAnim;
    sf::Texture texStillL, texStillR, texWalkLeft, texWalkRight;
    sf::Texture texRunLeft, texRunRight, texAttackLeft, texAttackRight;

public:
    Sonic() {
        texStillL.loadFromFile("../Data/0left_Still.png");    stillL.init(texStillL, 40, 35, 1, 0.f);
        texStillR.loadFromFile("../Data/0right_Still.png");   stillR.init(texStillR, 40, 35, 1, 0.f);
        texWalkLeft.loadFromFile("../Data/0jog_left.png");    walkLeft.init(texWalkLeft, 40, 35, 8, 0.09f);
        texWalkRight.loadFromFile("../Data/0jog_right.png");  walkRight.init(texWalkRight, 40, 35, 8, 0.09f);
        texRunLeft.loadFromFile("../Data/0left_run.png");     runLeft.init(texRunLeft, 40, 35, 6, 0.08f);
        texRunRight.loadFromFile("../Data/0right_run.png");   runRight.init(texRunRight, 40, 35, 6, 0.08f);
        texAttackLeft.loadFromFile("../Data/0upL.png");       attackLeft.init(texAttackLeft, 40, 35, 3, 0.12f);
        texAttackRight.loadFromFile("../Data/0upR.png");      attackRight.init(texAttackRight, 40, 35, 3, 0.12f);

        currentAnim = &stillR;
        previousAnim = nullptr;
    }

    void update(char** levelGrid, bool isControlled, float deltaTime) override {
        Character::update(levelGrid, isControlled, deltaTime);

        if (!isOnGround) {
            currentAnim = (velocityX < 0 ? &attackLeft : &attackRight);
        }
        else if (std::fabs(velocityX) > movementSpeed * 1.5f) {
            currentAnim = (velocityX < 0 ? &runLeft : &runRight);
        }
        else if (std::fabs(velocityX) > 0.f) {
            currentAnim = (velocityX < 0 ? &walkLeft : &walkRight);
        }
        else {
            if (currentAnim == &walkLeft || currentAnim == &runLeft || currentAnim == &attackLeft)
                currentAnim = &stillL;
            else
                currentAnim = &stillR;
        }

        if (currentAnim != previousAnim) {
            currentAnim->reset();
            previousAnim = currentAnim;
        }

        currentAnim->setPosition(posX, posY);
        currentAnim->update(deltaTime);
    }

    void draw(sf::RenderWindow& win, float offsetX) override {

        hb.shape.setPosition(posX + hitboxOffsetX - offsetX, posY + hitboxOffsetY);
        win.draw(hb.shape);
        currentAnim->setPosition(posX, posY);
        currentAnim->draw(win, offsetX);
    }
};
