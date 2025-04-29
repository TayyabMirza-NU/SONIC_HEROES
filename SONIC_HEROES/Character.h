#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Animation.h"
#include <cmath>

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
        : width(w), height(h) {
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
};

// ======================== Platform ========================
class Platform {
public:
    static bool checkCollision(const sf::FloatRect& bbox, char** grid) {
        int left = int(bbox.left / GameConstants::CELL_SIZE);
        int right = int((bbox.left + bbox.width) / GameConstants::CELL_SIZE);
        int top = int(bbox.top / GameConstants::CELL_SIZE);
        int bottom = int((bbox.top + bbox.height) / GameConstants::CELL_SIZE);
        for (int i = top; i <= bottom; ++i) {
            for (int j = left; j <= right; ++j) {
                if (i >= 0 && i < 14 && j >= 0 && j < 110 && grid[i][j] == 'w')
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
        gravityAcceleration(1.f), terminalVelocity(20.f), movementSpeed(5.f),
        spriteWidth(int(24 * 2.5f)), spriteHeight(int(35 * 2.5f)),
        hitboxOffsetX(int(8 * 2.5f)), hitboxOffsetY(int(2 * 2.5f)),
        hb(spriteWidth - 2 * hitboxOffsetX,
            spriteHeight - hitboxOffsetY)
    {
    }

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

        // Horizontal movement
        posX += velocityX;
        if (velocityX != 0) {
            float midY = posY + spriteHeight / 2.0f;
            int rowMid = int(midY / GameConstants::CELL_SIZE);
            int colLeft = int((posX + hitboxOffsetX) / GameConstants::CELL_SIZE);
            int colRight = int((posX + spriteWidth - hitboxOffsetX) / GameConstants::CELL_SIZE);
            if (rowMid >= 0 && rowMid < 14) {
                if (velocityX > 0 && levelGrid[rowMid][colRight] == 'w') posX -= velocityX;
                if (velocityX < 0 && levelGrid[rowMid][colLeft] == 'w') posX -= velocityX;
            }
        }

        // Vertical movement & collision
        float nextY = posY + velocityY;
        sf::FloatRect vbox(
            posX + hitboxOffsetX,
            nextY + hitboxOffsetY,
            spriteWidth - 2 * hitboxOffsetX,
            spriteHeight - hitboxOffsetY
        );
        if (Platform::checkCollision(vbox, levelGrid)) {
            isOnGround = true;
            velocityY = 0.f;
            int row = int((vbox.top + vbox.height) / GameConstants::CELL_SIZE);
            posY = row * GameConstants::CELL_SIZE - (spriteHeight - hitboxOffsetY);
        }
        else {
            isOnGround = false;
            posY = nextY;
            velocityY += gravityAcceleration;
            if (velocityY > terminalVelocity) velocityY = terminalVelocity;
        }

        // Sync hitbox
        hb.setSize(
            spriteWidth - 2 * hitboxOffsetX,
            spriteHeight - hitboxOffsetY
        );
        hb.setPosition(
            posX + hitboxOffsetX,
            posY + hitboxOffsetY
        );

        anim.setPosition(posX, posY);
        anim.update(deltaTime);
    }

    int getX() const { return int(posX); }

    virtual void draw(sf::RenderWindow& window, float offsetX) {
        // Draw hitbox (behind the character)
        hb.shape.move(-offsetX, 0.f);
        window.draw(hb.shape);
        hb.shape.move(offsetX, 0.f);

        // Draw sprite
        anim.draw(window, offsetX);
    }
};

// ======================== Sonic Character ========================
class Sonic : public Character {
private:
    Animation stillL, stillR, walkLeft, walkRight, runLeft, runRight, attackLeft, attackRight;
    Animation* currentAnim;
    Animation* previousAnim;
    sf::Texture texStillL, texStillR, texWalkLeft, texWalkRight,
        texRunLeft, texRunRight, texAttackLeft, texAttackRight;
public:
    Sonic() {
        texStillL.loadFromFile("../Data/0left_Still.png");    stillL.init(texStillL, 40, 35, 1, 0.f);
        texStillR.loadFromFile("../Data/0right_Still.png");   stillR.init(texStillR, 40, 35, 1, 0.f);
        texWalkLeft.loadFromFile("../Data/0jog_left.png");    walkLeft.init(texWalkLeft, 40, 35, 8, 0.09f);
        texWalkRight.loadFromFile("../Data/0jog_right.png");  walkRight.init(texWalkRight, 40, 35, 8, 0.09f);
        texRunLeft.loadFromFile("../Data/0left_run.png");      runLeft.init(texRunLeft, 40, 35, 6, 0.08f);
        texRunRight.loadFromFile("../Data/0right_run.png");    runRight.init(texRunRight, 40, 35, 6, 0.08f);
        texAttackLeft.loadFromFile("../Data/0upL.png");        attackLeft.init(texAttackLeft, 40, 35, 3, 0.12f);
        texAttackRight.loadFromFile("../Data/0upR.png");       attackRight.init(texAttackRight, 40, 35, 3, 0.12f);

        currentAnim = &stillR;
        previousAnim = nullptr;
    }

    void handleInput() override {
        Character::handleInput();
    }

    void update(char** levelGrid, bool isControlled, float deltaTime) override {
        if (isControlled) handleInput();
        Character::update(levelGrid, isControlled, deltaTime);

        // Determine animation state
        if (!isOnGround) {
            currentAnim = (velocityX < 0 ? &attackLeft : &attackRight);
        }
        else if (std::fabs(velocityX) > movementSpeed * 1.5f) {
            currentAnim = (velocityX < 0 ? &runLeft : &runRight);
        }
        else if (std::fabs(velocityX) > 0) {
            currentAnim = (velocityX < 0 ? &walkLeft : &walkRight);
        }
        else {
            currentAnim = (currentAnim == &walkLeft || currentAnim == &runLeft || currentAnim == &attackLeft)
                ? &stillL : &stillR;
        }

        // Reset animation if changed
        if (currentAnim != previousAnim) {
            currentAnim->reset();
            previousAnim = currentAnim;
        }

        currentAnim->setPosition(posX, posY);
        currentAnim->update(deltaTime);
    }

    void draw(sf::RenderWindow& win, float offsetX) override {
        // Draw hitbox
        hb.shape.move(-offsetX, 0.f);
        win.draw(hb.shape);
        hb.shape.move(offsetX, 0.f);

        // Draw the current Sonic animation
        currentAnim->draw(win, offsetX);
    }
};