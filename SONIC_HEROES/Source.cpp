



#include "Game.h"


int main() {
    // Correctly instantiate the Game object
    Game game; 
    game.run();  // Run the game
    return 0;
}










//#include <iostream>
//#include <fstream>
//#include <cmath>
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Window.hpp>
//
//using namespace sf;
//using namespace std;
//
//// ======================== Constants ========================
//const int SCREEN_X = 1200;
//const int SCREEN_Y = 900;
//const int CELL_SIZE = 64;
//const int LEVEL_HEIGHT = 14;
//const int LEVEL_WIDTH = 110;
//const int MAX_LEVELS = 4;
//const int MAX_ENEMIES = 5;
//const int MAX_COLLECTIBLES = 5;
//const int MAX_CHARACTERS = 3;
//const int MAX_FRAMES = 10;
//
//// ======================== Animation ========================
//class Animation {
//private:
//    Sprite sprite;
//    IntRect frames[MAX_FRAMES];
//    int frameCount;
//    int currentFrame;
//    float frameTime;
//    float elapsedTime;
//    float scale;
//public:
//    Animation() : frameCount(0), currentFrame(0), frameTime(0.1f), elapsedTime(0), scale(2.5f) {}
//
//    void init(Texture& tex, int fw, int fh, int count, float tpf) {
//        sprite.setTexture(tex);
//        sprite.setScale(scale, scale);
//        frameCount = count;
//        for (int i = 0; i < count && i < MAX_FRAMES; ++i)
//            frames[i] = IntRect(i * fw, 0, fw, fh);
//        frameTime = tpf;
//        currentFrame = 0;
//        elapsedTime = 0;
//        sprite.setTextureRect(frames[0]);
//    }
//
//    void update(float dt) {
//        elapsedTime += dt;
//        if (elapsedTime >= frameTime && frameCount > 0) {
//            elapsedTime -= frameTime;
//            currentFrame = (currentFrame + 1) % frameCount;
//            sprite.setTextureRect(frames[currentFrame]);
//        }
//    }
//
//    void setPosition(float x, float y) { sprite.setPosition(x, y); }
//
//    void draw(RenderWindow& win, float offsetX) {
//        sprite.move(-offsetX, 0.f);
//        win.draw(sprite);
//        sprite.move(offsetX, 0.f);
//    }
//};
//
//// ======================== Platform ========================
//class Platform {
//public:
//    static bool checkCollision(const FloatRect& bbox, char** grid) {
//        int left = int(bbox.left / CELL_SIZE);
//        int right = int((bbox.left + bbox.width) / CELL_SIZE);
//        int top = int(bbox.top / CELL_SIZE);
//        int bottom = int((bbox.top + bbox.height) / CELL_SIZE);
//        for (int i = top; i <= bottom; ++i) {
//            for (int j = left; j <= right; ++j) {
//                if (i >= 0 && i < LEVEL_HEIGHT && j >= 0 && j < LEVEL_WIDTH && grid[i][j] == 'w')
//                    return true;
//            }
//        }
//        return false;
//    }
//};
//
//// ======================== Character ========================
//class Character {
//protected:
//    float posX, posY;
//    float velocityX, velocityY;
//    bool isOnGround;
//    float gravityAcceleration;
//    float terminalVelocity;
//    float movementSpeed;
//    int spriteWidth, spriteHeight;
//    int hitboxOffsetX, hitboxOffsetY;
//    Animation anim;
//public:
//    Character()
//        : posX(100.f), posY(100.f), velocityX(0.f), velocityY(0.f),
//        isOnGround(false), gravityAcceleration(1.f), terminalVelocity(20.f), movementSpeed(4.f),
//        spriteWidth(int(24 * 2.5f)), spriteHeight(int(35 * 2.5f)),
//        hitboxOffsetX(int(8 * 2.5f)), hitboxOffsetY(int(2 * 2.5f))
//    {
//    }
//
//    virtual void handleInput() {
//        velocityX = 0.f;
//        float speed = movementSpeed;
//        // Running when Shift is held
//        if (Keyboard::isKeyPressed(Keyboard::LShift) && isOnGround)
//            speed *= 2.f;
//        if (Keyboard::isKeyPressed(Keyboard::A)) velocityX = -speed;
//        else if (Keyboard::isKeyPressed(Keyboard::D)) velocityX = speed;
//        if (Keyboard::isKeyPressed(Keyboard::Space) && isOnGround) {
//            velocityY = -20.f;
//            isOnGround = false;
//        }
//    }
//
//    virtual void update(char** levelGrid, bool isControlled, float deltaTime) {
//        if (isControlled) handleInput();
//        posX += velocityX;
//
//        // Horizontal collision (side tiles only)
//        if (velocityX != 0) {
//            float midY = posY + spriteHeight / 2.0f;
//            int rowMid = int(midY / CELL_SIZE);
//            int colLeft = int((posX + hitboxOffsetX) / CELL_SIZE);
//            int colRight = int((posX + spriteWidth - hitboxOffsetX) / CELL_SIZE);
//            if (rowMid >= 0 && rowMid < LEVEL_HEIGHT) {
//                if (velocityX > 0 && levelGrid[rowMid][colRight] == 'w') posX -= velocityX;
//                if (velocityX < 0 && levelGrid[rowMid][colLeft] == 'w') posX -= velocityX;
//            }
//        }
//
//        // Vertical movement & collision
//        float nextY = posY + velocityY;
//        FloatRect vbox(posX + hitboxOffsetX, nextY + hitboxOffsetY,
//            spriteWidth - 2 * hitboxOffsetX, spriteHeight - hitboxOffsetY);
//        if (Platform::checkCollision(vbox, levelGrid)) {
//            // Land on floor
//            isOnGround = true;
//            velocityY = 0.f;
//            int row = int((vbox.top + vbox.height) / CELL_SIZE);
//            posY = row * CELL_SIZE - (spriteHeight - hitboxOffsetY);
//        }
//        else {
//            isOnGround = false;
//            posY = nextY;
//            velocityY += gravityAcceleration;
//            if (velocityY > terminalVelocity) velocityY = terminalVelocity;
//        }
//
//        anim.setPosition(posX, posY);
//        anim.update(deltaTime);
//    }
//
//    int getX() const { return int(posX); }
//    virtual void draw(RenderWindow& window, float offsetX) {
//        anim.draw(window, offsetX);
//    }
//};
//
//// ======================== Sonic Character ========================
//class Sonic : public Character {
//private:
//    Animation stillL, stillR, walkLeft, walkRight, runLeft, runRight, attackLeft, attackRight;
//    Animation* currentAnim;
//    Texture texStillL, texStillR, texWalkLeft, texWalkRight, texRunLeft, texRunRight, texAttackLeft, texAttackRight;
//public:
//    Sonic() {
//        texStillL.loadFromFile("../Data/0left_Still.png"); stillL.init(texStillL, 40, 35, 1, 0.f);
//        texStillR.loadFromFile("../Data/0right_Still.png"); stillR.init(texStillR, 40, 35, 1, 0.f);
//        texWalkLeft.loadFromFile("../Data/0jog_left.png"); walkLeft.init(texWalkLeft, 40, 35, 4, 0.1f);
//        texWalkRight.loadFromFile("../Data/0jog_right.png"); walkRight.init(texWalkRight, 40, 35, 4, 0.1f);
//        texRunLeft.loadFromFile("../Data/0left_run.png"); runLeft.init(texRunLeft, 40, 35, 6, 0.08f);
//        texRunRight.loadFromFile("../Data/0right_run.png"); runRight.init(texRunRight, 40, 35, 6, 0.08f);
//        texAttackLeft.loadFromFile("../Data/0upL.png"); attackLeft.init(texAttackLeft, 40, 35, 3, 0.12f);
//        texAttackRight.loadFromFile("../Data/0upR.png"); attackRight.init(texAttackRight, 40, 35, 3, 0.12f);
//        currentAnim = &stillR;
//    }
//
//    void handleInput() override { Character::handleInput(); }
//
//    void update(char** levelGrid, bool isControlled, float deltaTime) override {
//        if (isControlled) handleInput();
//        Character::update(levelGrid, isControlled, deltaTime);
//        if (!isOnGround) {
//            currentAnim = (velocityX < 0 ? &attackLeft : &attackRight);
//        }
//        else if (fabs(velocityX) > movementSpeed * 1.5f) {
//            currentAnim = (velocityX < 0 ? &runLeft : &runRight);
//        }
//        else if (fabs(velocityX) > 0) {
//            currentAnim = (velocityX < 0 ? &walkLeft : &walkRight);
//        }
//        else {
//            currentAnim = (currentAnim == &walkLeft || currentAnim == &runLeft || currentAnim == &attackLeft)
//                ? &stillL : &stillR;
//        }
//        currentAnim->setPosition(posX, posY);
//        currentAnim->update(deltaTime);
//    }
//
//    void draw(RenderWindow& win, float offsetX) override { currentAnim->draw(win, offsetX); }
//};
//
//// ======================== Enemy & Collectible ========================
//class Enemy {
//protected:
//    float x, y;
//    Animation anim;
//    Texture tex;
//public:
//    Enemy(float sx = 0.f, float sy = 0.f) :x(sx), y(sy) {}
//    virtual void load(const string& path) { tex.loadFromFile(path); anim.init(tex, 24, 35, 1, 0.1f); }
//    virtual void update(char** lvl, float dt) { anim.setPosition(x, y); anim.update(dt); }
//    virtual void draw(RenderWindow& win, float offsetX) { anim.draw(win, offsetX); }
//};
//class BatBrain :public Enemy { public:BatBrain(float sx, float sy) :Enemy(sx, sy) { load("../Data/0left_still.png"); } };
//class BeeBot :public Enemy { public:BeeBot(float sx, float sy) :Enemy(sx, sy) { load("../Data/0left_still.png"); } };
//class Motobug :public Enemy { public:Motobug(float sx, float sy) :Enemy(sx, sy) { load("../Data/0left_still.png"); } };
//class CrabMeat :public Enemy { public:CrabMeat(float sx, float sy) :Enemy(sx, sy) { load("../Data/0left_still.png"); } };
//class EggStinger :public Enemy { public:EggStinger(float sx, float sy) :Enemy(sx, sy) { load("../Data/0left_still.png"); } };
//
//class Collectible {
//protected:
//    float x, y;
//    Animation anim;
//    Texture tex;
//public:
//    Collectible(float sx = 0.f, float sy = 0.f) :x(sx), y(sy) {}
//    virtual void load(const string& path) { tex.loadFromFile(path); anim.init(tex, 24, 35, 1, 0.1f); }
//    virtual void applyEffect(Character* c) {}
//    virtual void update(float dt) { anim.setPosition(x, y); anim.update(dt); }
//    virtual void draw(RenderWindow& win, float offsetX) { anim.draw(win, offsetX); }
//};
//class Ring :public Collectible { public:Ring(float sx, float sy) :Collectible(sx, sy) { load("../Data/0left_still.png"); } void applyEffect(Character* c) override {} };
//class ExtraLife :public Collectible { public:ExtraLife(float sx, float sy) :Collectible(sx, sy) { load("../Data/0left_still.png"); } void applyEffect(Character* c) override {} };
//class SpecialBoost :public Collectible { public:SpecialBoost(float sx, float sy) :Collectible(sx, sy) { load("../Data/0left_still.png"); } void applyEffect(Character* c) override {} };
//
//// ======================== Player ========================
//class Player {
//private:
//    Character* chars[MAX_CHARACTERS];
//    int idx;
//public:
//    Player() :idx(0) { chars[0] = new Sonic(); chars[1] = new Sonic(); chars[2] = new Sonic(); }
//    void switchChar() { idx = (idx + 1) % MAX_CHARACTERS; }
//    void update(char** lvl, float dt) { chars[idx]->update(lvl, true, dt); }
//    void draw(RenderWindow& win, float offsetX) { chars[idx]->draw(win, offsetX); }
//    int getX() const { return chars[idx]->getX(); }
//};
//
//// ======================== Level ========================
//class Level {
//public:
//    char** grid;
//    Texture wallTex;
//    Sprite wallSprite;
//    Level(int num) {
//        grid = new char* [LEVEL_HEIGHT];
//        for (int i = 0;i < LEVEL_HEIGHT;++i) grid[i] = new char[LEVEL_WIDTH] {};
//        wallTex.loadFromFile("../Data/brick1.png"); wallSprite.setTexture(wallTex);
//        switch (num) {
//        case 0: for (int j = 0;j < LEVEL_WIDTH;++j) grid[LEVEL_HEIGHT - 3][j] = 'w'; break;
//        case 1: for (int j = 0;j < LEVEL_WIDTH;++j) grid[LEVEL_HEIGHT - 3][j] = 'w'; for (int j = 10;j < 20;++j) grid[LEVEL_HEIGHT - 6][j] = 'w'; break;
//        case 2: for (int j = 0;j < LEVEL_WIDTH;++j) if (j < 15 || j>25) grid[LEVEL_HEIGHT - 3][j] = 'w'; break;
//        case 3: for (int step = 0;step < 5;++step) for (int j = 0;j < 10;++j) grid[LEVEL_HEIGHT - 3 - step][j + step * 10] = 'w'; for (int j = 50;j < LEVEL_WIDTH;++j) grid[LEVEL_HEIGHT - 3][j] = 'w'; break;
//        }
//    }
//    ~Level() { for (int i = 0;i < LEVEL_HEIGHT;++i) delete[] grid[i]; delete[] grid; }
//    void draw(RenderWindow& win, float offsetX) {
//        for (int i = 0;i < LEVEL_HEIGHT;++i) for (int j = 0;j < LEVEL_WIDTH;++j) if (grid[i][j] == 'w') {
//            wallSprite.setPosition(j * CELL_SIZE - offsetX, i * CELL_SIZE);
//            win.draw(wallSprite);
//        }
//    }
//};
//
//// ======================== Menu ========================
//class MenuScreen {
//private:
//    Font font;
//    Text title;
//    Text options[MAX_LEVELS];
//    int selected;
//public:
//    MenuScreen() : selected(0) {
//        font.loadFromFile("../Data/Jaro/Jaro.ttf");
//        title.setFont(font);
//        title.setString("Select Level");
//        title.setCharacterSize(60);
//        title.setFillColor(Color::White);
//        title.setPosition((SCREEN_X - title.getLocalBounds().width) / 2, 100);
//        for (int i = 0; i < MAX_LEVELS; ++i) {
//            options[i].setFont(font);
//            options[i].setString("Level " + to_string(i + 1));
//            options[i].setCharacterSize(48);
//            options[i].setPosition((SCREEN_X - 200) / 2, 200 + i * 80);
//        }
//    }
//    int handleInput(const Event& ev) {
//        if (ev.type == Event::KeyPressed) {
//            if (ev.key.code == Keyboard::Up) {
//                selected = (selected + MAX_LEVELS - 1) % MAX_LEVELS;
//            }
//            else if (ev.key.code == Keyboard::Down) {
//                selected = (selected + 1) % MAX_LEVELS;
//            }
//            else if (ev.key.code == Keyboard::Enter) {
//                return selected;
//            }
//        }
//        return -1;
//    }
//    void reset() { selected = 0; }
//    void draw(RenderWindow& win) {
//        win.clear();
//        win.draw(title);
//        for (int i = 0; i < MAX_LEVELS; ++i) {
//            options[i].setFillColor(i == selected ? Color::Yellow : Color::White);
//            win.draw(options[i]);
//        }
//        win.display();
//    }
//};
//
//// ======================== Game ========================
//class Game {
//private:
//    RenderWindow window;
//    MenuScreen menu;
//    Level* levels[MAX_LEVELS];
//    int curLevel;
//    Player player;
//    Enemy* enemies[MAX_ENEMIES];
//    Collectible* collects[MAX_COLLECTIBLES];
//    Music music;
//public:
//    Game()
//        : window(VideoMode(SCREEN_X, SCREEN_Y), "Sonic-OOP Improved"), curLevel(-1) {
//        window.setFramerateLimit(60);
//        music.openFromFile("../Data/labrynth.ogg");
//        music.setLoop(true);
//        music.play();
//        for (int i = 0; i < MAX_LEVELS; ++i)
//            levels[i] = new Level(i);
//        // Initialize enemies
//        enemies[0] = new BatBrain(300, 300);
//        enemies[1] = new BeeBot(500, 200);
//        enemies[2] = new Motobug(700, 300);
//        enemies[3] = new CrabMeat(900, 200);
//        enemies[4] = new EggStinger(1100, 100);
//        // Initialize collectibles
//        collects[0] = new Ring(400, 400);
//        collects[1] = new ExtraLife(600, 350);
//        collects[2] = new SpecialBoost(800, 400);
//        collects[3] = new Ring(1000, 300);
//        collects[4] = new Ring(200, 500);
//    }
//
//    void run() {
//        Event ev;
//        Clock clock;
//        while (window.isOpen()) {
//            if (curLevel < 0) {
//                while (window.pollEvent(ev)) {
//                    if (ev.type == Event::Closed)
//                        window.close();
//                    int sel = menu.handleInput(ev);
//                    if (sel >= 0) {
//                        curLevel = sel;
//                        menu.reset();
//                    }
//                }
//                menu.draw(window);
//                continue;
//            }
//
//            float dt = clock.restart().asSeconds();
//            while (window.pollEvent(ev)) {
//                if (ev.type == Event::Closed)
//                    window.close();
//                if (ev.type == Event::KeyPressed) {
//                    if (ev.key.code == Keyboard::Tab)
//                        player.switchChar();
//                    if (ev.key.code == Keyboard::M)
//                        curLevel = -1;
//                }
//            }
//
//            // Update logic
//            player.update(levels[curLevel]->grid, dt);
//            for (int i = 0; i < MAX_ENEMIES; ++i)
//                enemies[i]->update(levels[curLevel]->grid, dt);
//            for (int j = 0; j < MAX_COLLECTIBLES; ++j)
//                collects[j]->update(dt);
//
//            // Draw logic with manual camera
//            window.clear();
//            float halfScreen = SCREEN_X / 2.f;
//            float levelWidth = LEVEL_WIDTH * CELL_SIZE;
//            float viewCenterX = player.getX() + CELL_SIZE / 2.f;
//            if (viewCenterX < halfScreen)
//                viewCenterX = halfScreen;
//            if (viewCenterX > levelWidth - halfScreen)
//                viewCenterX = levelWidth - halfScreen;
//            float offsetX = viewCenterX - halfScreen;
//
//            levels[curLevel]->draw(window, offsetX);
//            for (int i = 0; i < MAX_COLLECTIBLES; ++i)
//                collects[i]->draw(window, offsetX);
//            player.draw(window, offsetX);
//            for (int i = 0; i < MAX_ENEMIES; ++i)
//                enemies[i]->draw(window, offsetX);
//
//            window.display();
//        }
//    }
//};
//
//
//int main() {
//    Game game;
//    game.run();
//    return 0;
//}




//#include <iostream>
//#include <fstream>
//#include <cmath>
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Window.hpp>
//
//using namespace sf;
//using namespace std;
//
//// ======================== Constants ========================
//const int SCREEN_X = 1200;
//const int SCREEN_Y = 900;
//const int CELL_SIZE = 64;
//const int LEVEL_HEIGHT = 14;
//const int LEVEL_WIDTH = 110;
//const int MAX_LEVELS = 4;
//const int MAX_ENEMIES = 5;
//const int MAX_COLLECTIBLES = 5;
//const int MAX_CHARACTERS = 3;
//const int MAX_FRAMES = 10;
//
//// Forward declarations
//class Level;
//
//// ======================== Animation ========================
//class Animation {
//private:
//    Sprite sprite;
//    IntRect frames[MAX_FRAMES];
//    int frameCount;
//    int currentFrame;
//    float frameTime;
//    float elapsedTime;
//    float scale;
//public:
//    Animation() : frameCount(0), currentFrame(0), frameTime(0.1f), elapsedTime(0), scale(2.5f) {}
//
//    void init(Texture& tex, int fw, int fh, int count, float tpf) {
//        sprite.setTexture(tex);
//        sprite.setScale(scale, scale);
//        frameCount = count;
//        for (int i = 0; i < count && i < MAX_FRAMES; ++i)
//            frames[i] = IntRect(i * fw, 0, fw, fh);
//        frameTime = tpf;
//        currentFrame = 0;
//        elapsedTime = 0;
//        sprite.setTextureRect(frames[0]);
//    }
//
//    void update(float dt) {
//        elapsedTime += dt;
//        if (elapsedTime >= frameTime && frameCount > 0) {
//            elapsedTime -= frameTime;
//            currentFrame = (currentFrame + 1) % frameCount;
//            sprite.setTextureRect(frames[currentFrame]);
//        }
//    }
//
//    void setPosition(float x, float y) { sprite.setPosition(x, y); }
//
//    void draw(RenderWindow& win, float offsetX) {
//        sprite.move(-offsetX, 0.f);
//        win.draw(sprite);
//        sprite.move(offsetX, 0.f);
//    }
//};
//
//// ======================== Platform ========================
//class Platform {
//public:
//    static bool checkCollision(const FloatRect& bbox, char** grid) {
//        int left = int(bbox.left / CELL_SIZE);
//        int right = int((bbox.left + bbox.width) / CELL_SIZE);
//        int top = int(bbox.top / CELL_SIZE);
//        int bottom = int((bbox.top + bbox.height) / CELL_SIZE);
//        for (int i = top; i <= bottom; ++i) {
//            for (int j = left; j <= right; ++j) {
//                if (i >= 0 && i < LEVEL_HEIGHT && j >= 0 && j < LEVEL_WIDTH && grid[i][j] == 'w')
//                    return true;
//            }
//        }
//        return false;
//    }
//};
//
//// ======================== Character ========================
//class Character {
//protected:
//    float posX, posY;
//    float velocityX, velocityY;
//    bool isOnGround;
//    float gravityAcceleration;
//    float terminalVelocity;
//    float movementSpeed;
//    int spriteWidth, spriteHeight;
//    int hitboxOffsetX, hitboxOffsetY;
//    Animation anim;
//public:
//    Character()
//        : posX(100.f), posY(100.f), velocityX(0.f), velocityY(0.f),
//        isOnGround(false), gravityAcceleration(1.f), terminalVelocity(20.f), movementSpeed(4.f),
//        spriteWidth(int(24 * 2.5f)), spriteHeight(int(35 * 2.5f)),
//        hitboxOffsetX(int(8 * 2.5f)), hitboxOffsetY(int(2 * 2.5f))
//    {
//    }
//
//    virtual void handleInput() {
//        velocityX = 0.f;
//        float speed = movementSpeed;
//        if (Keyboard::isKeyPressed(Keyboard::LShift) && isOnGround)
//            speed *= 2.f;
//        if (Keyboard::isKeyPressed(Keyboard::A)) velocityX = -speed;
//        else if (Keyboard::isKeyPressed(Keyboard::D)) velocityX = speed;
//        if (Keyboard::isKeyPressed(Keyboard::Space) && isOnGround) {
//            velocityY = -20.f;
//            isOnGround = false;
//        }
//    }
//
//    virtual void update(char** levelGrid, bool isControlled, float deltaTime) {
//        if (isControlled) handleInput();
//        posX += velocityX;
//
//        if (velocityX != 0) {
//            float midY = posY + spriteHeight / 2.0f;
//            int rowMid = int(midY / CELL_SIZE);
//            int colLeft = int((posX + hitboxOffsetX) / CELL_SIZE);
//            int colRight = int((posX + spriteWidth - hitboxOffsetX) / CELL_SIZE);
//            if (rowMid >= 0 && rowMid < LEVEL_HEIGHT) {
//                if (velocityX > 0 && levelGrid[rowMid][colRight] == 'w') posX -= velocityX;
//                if (velocityX < 0 && levelGrid[rowMid][colLeft] == 'w') posX -= velocityX;
//            }
//        }
//
//        float nextY = posY + velocityY;
//        FloatRect vbox(posX + hitboxOffsetX, nextY + hitboxOffsetY,
//            spriteWidth - 2 * hitboxOffsetX, spriteHeight - hitboxOffsetY);
//        if (Platform::checkCollision(vbox, levelGrid)) {
//            isOnGround = true;
//            velocityY = 0.f;
//            int row = int((vbox.top + vbox.height) / CELL_SIZE);
//            posY = row * CELL_SIZE - (spriteHeight - hitboxOffsetY);
//        }
//        else {
//            isOnGround = false;
//            posY = nextY;
//            velocityY += gravityAcceleration;
//            if (velocityY > terminalVelocity) velocityY = terminalVelocity;
//        }
//
//        anim.setPosition(posX, posY);
//        anim.update(deltaTime);
//    }
//
//    int getX() const { return int(posX); }
//    virtual void draw(RenderWindow& window, float offsetX) {
//        anim.draw(window, offsetX);
//    }
//};
//
//// ======================== Sonic Character ========================
//class Sonic : public Character {
//private:
//    Animation stillL, stillR, walkLeft, walkRight, runLeft, runRight, attackLeft, attackRight;
//    Animation* currentAnim;
//    Texture texStillL, texStillR, texWalkLeft, texWalkRight, texRunLeft, texRunRight, texAttackLeft, texAttackRight;
//public:
//    Sonic() {
//        texStillL.loadFromFile("../Data/0left_Still.png"); stillL.init(texStillL, 40, 35, 1, 0.f);
//        texStillR.loadFromFile("../Data/0right_Still.png"); stillR.init(texStillR, 40, 35, 1, 0.f);
//        texWalkLeft.loadFromFile("../Data/0jog_left.png"); walkLeft.init(texWalkLeft, 40, 35, 4, 0.1f);
//        texWalkRight.loadFromFile("../Data/0jog_right.png"); walkRight.init(texWalkRight, 40, 35, 4, 0.1f);
//        texRunLeft.loadFromFile("../Data/0left_run.png"); runLeft.init(texRunLeft, 40, 35, 6, 0.08f);
//        texRunRight.loadFromFile("../Data/0right_run.png"); runRight.init(texRunRight, 40, 35, 6, 0.08f);
//        texAttackLeft.loadFromFile("../Data/0upL.png"); attackLeft.init(texAttackLeft, 40, 35, 3, 0.12f);
//        texAttackRight.loadFromFile("../Data/0upR.png"); attackRight.init(texAttackRight, 40, 35, 3, 0.12f);
//        currentAnim = &stillR;
//    }
//
//    void handleInput() override { Character::handleInput(); }
//
//    void update(char** levelGrid, bool isControlled, float deltaTime) override {
//        if (isControlled) handleInput();
//        Character::update(levelGrid, isControlled, deltaTime);
//        if (!isOnGround) {
//            currentAnim = (velocityX < 0 ? &attackLeft : &attackRight);
//        }
//        else if (fabs(velocityX) > movementSpeed * 1.5f) {
//            currentAnim = (velocityX < 0 ? &runLeft : &runRight);
//        }
//        else if (fabs(velocityX) > 0) {
//            currentAnim = (velocityX < 0 ? &walkLeft : &walkRight);
//        }
//        else {
//            currentAnim = (currentAnim == &walkLeft || currentAnim == &runLeft || currentAnim == &attackLeft)
//                ? &stillL : &stillR;
//        }
//        currentAnim->setPosition(posX, posY);
//        currentAnim->update(deltaTime);
//    }
//
//    void draw(RenderWindow& win, float offsetX) override { currentAnim->draw(win, offsetX); }
//};
//
//// ======================== Enemy & Collectible ========================
//class Enemy {
//protected:
//    float x, y;
//    Animation anim;
//    Texture tex;
//public:
//    Enemy(float sx = 0.f, float sy = 0.f) :x(sx), y(sy) {}
//    virtual void load(const string& path) { tex.loadFromFile(path); anim.init(tex, 24, 35, 1, 0.1f); }
//    virtual void update(char** lvl, float dt) { anim.setPosition(x, y); anim.update(dt); }
//    virtual void draw(RenderWindow& win, float offsetX) { anim.draw(win, offsetX); }
//};
//class BatBrain :public Enemy { public:BatBrain(float sx, float sy) :Enemy(sx, sy) { load("../Data/0left_still.png"); } };
//class BeeBot :public Enemy { public:BeeBot(float sx, float sy) :Enemy(sx, sy) { load("../Data/0left_still.png"); } };
//class Motobug :public Enemy { public:Motobug(float sx, float sy) :Enemy(sx, sy) { load("../Data/0left_still.png"); } };
//class CrabMeat :public Enemy { public:CrabMeat(float sx, float sy) :Enemy(sx, sy) { load("../Data/0left_still.png"); } };
//class EggStinger :public Enemy { public:EggStinger(float sx, float sy) :Enemy(sx, sy) { load("../Data/0left_still.png"); } };
//
//class Collectible {
//protected:
//    float x, y;
//    Animation anim;
//    Texture tex;
//public:
//    Collectible(float sx = 0.f, float sy = 0.f) :x(sx), y(sy) {}
//    virtual void load(const string& path) { tex.loadFromFile(path); anim.init(tex, 24, 35, 1, 0.1f); }
//    virtual void applyEffect(Character* c) {}
//    virtual void update(float dt) { anim.setPosition(x, y); anim.update(dt); }
//    virtual void draw(RenderWindow& win, float offsetX) { anim.draw(win, offsetX); }
//};
//class Ring :public Collectible { public:Ring(float sx, float sy) :Collectible(sx, sy) { load("../Data/0left_still.png"); } void applyEffect(Character* c) override {} };
//class ExtraLife :public Collectible { public:ExtraLife(float sx, float sy) :Collectible(sx, sy) { load("../Data/0left_still.png"); } void applyEffect(Character* c) override {} };
//class SpecialBoost :public Collectible { public:SpecialBoost(float sx, float sy) :Collectible(sx, sy) { load("../Data/0left_still.png"); } void applyEffect(Character* c) override {} };
//
//// ======================== Level ========================
//class Level {
//public:
//    char** grid;
//    Texture wallTex;
//    Sprite wallSprite;
//    Level(int num) {
//        grid = new char* [LEVEL_HEIGHT];
//        for (int i = 0;i < LEVEL_HEIGHT;++i) grid[i] = new char[LEVEL_WIDTH] {};
//        wallTex.loadFromFile("../Data/brick1.png"); wallSprite.setTexture(wallTex);
//        switch (num) {
//        case 0: for (int j = 0;j < LEVEL_WIDTH;++j) grid[LEVEL_HEIGHT - 3][j] = 'w'; break;
//        case 1: for (int j = 0;j < LEVEL_WIDTH;++j) grid[LEVEL_HEIGHT - 3][j] = 'w'; for (int j = 10;j < 20;++j) grid[LEVEL_HEIGHT - 6][j] = 'w'; break;
//        case 2: for (int j = 0;j < LEVEL_WIDTH;++j) if (j < 15 || j>25) grid[LEVEL_HEIGHT - 3][j] = 'w'; break;
//        case 3: for (int step = 0;step < 5;++step) for (int j = 0;j < 10;++j) grid[LEVEL_HEIGHT - 3 - step][j + step * 10] = 'w'; for (int j = 50;j < LEVEL_WIDTH;++j) grid[LEVEL_HEIGHT - 3][j] = 'w'; break;
//        }
//    }
//    ~Level() { for (int i = 0;i < LEVEL_HEIGHT;++i) delete[] grid[i]; delete[] grid; }
//    void draw(RenderWindow& win, float offsetX) {
//        for (int i = 0;i < LEVEL_HEIGHT;++i) for (int j = 0;j < LEVEL_WIDTH;++j) if (grid[i][j] == 'w') {
//            wallSprite.setPosition(j * CELL_SIZE - offsetX, i * CELL_SIZE);
//            win.draw(wallSprite);
//        }
//    }
//};
//
//// ======================== Menu ========================
//class MenuScreen {
//private:
//    Font font;
//    Text title;
//    Text options[MAX_LEVELS];
//    int selected;
//public:
//    MenuScreen() : selected(0) {
//        font.loadFromFile("../Data/Jaro/Jaro.ttf");
//        title.setFont(font);
//        title.setString("Select Level");
//        title.setCharacterSize(60);
//        title.setFillColor(Color::White);
//        title.setPosition((SCREEN_X - title.getLocalBounds().width) / 2, 100);
//        for (int i = 0; i < MAX_LEVELS; ++i) {
//            options[i].setFont(font);
//            options[i].setString("Level " + to_string(i + 1));
//            options[i].setCharacterSize(48);
//            options[i].setPosition((SCREEN_X - 200) / 2, 200 + i * 80);
//        }
//    }
//    int handleInput(const Event& ev) {
//        if (ev.type == Event::KeyPressed) {
//            if (ev.key.code == Keyboard::Up) {
//                selected = (selected + MAX_LEVELS - 1) % MAX_LEVELS;
//            }
//            else if (ev.key.code == Keyboard::Down) {
//                selected = (selected + 1) % MAX_LEVELS;
//            }
//            else if (ev.key.code == Keyboard::Enter) {
//                return selected;
//            }
//        }
//        return -1;
//    }
//    void reset() { selected = 0; }
//    void draw(RenderWindow& win) {
//        win.clear();
//        win.draw(title);
//        for (int i = 0; i < MAX_LEVELS; ++i) {
//            options[i].setFillColor(i == selected ? Color::Yellow : Color::White);
//            win.draw(options[i]);
//        }
//        win.display();
//    }
//};
//
//// ======================== Player (aggregation with Level) ========================
//class Player {
//private:
//    Character* chars[MAX_CHARACTERS];
//    int idx;
//    Level* level; // aggregated level reference, not owned
//public:
//    Player() : idx(0), level(nullptr) {
//        // initialize roster
//        for (int i = 0; i < MAX_CHARACTERS; ++i)
//            chars[i] = new Sonic();
//    }
//    ~Player() {
//        for (int i = 0; i < MAX_CHARACTERS; ++i)
//            delete chars[i];
//    }
//    void setLevel(Level* lvl) { level = lvl; }
//    void switchChar() { idx = (idx + 1) % MAX_CHARACTERS; }
//    void update(float deltaTime) {
//        if (level)
//            chars[idx]->update(level->grid, true, deltaTime);
//    }
//    void draw(RenderWindow& win, float offsetX) { chars[idx]->draw(win, offsetX); }
//    int getX() const { return chars[idx]->getX(); }
//};
//
//// ======================== Game ========================
//class Game {
//private:
//    RenderWindow window;
//    MenuScreen menu;
//    Level* levels[MAX_LEVELS];
//    int curLevel;
//    Player player;
//    Enemy* enemies[MAX_ENEMIES];
//    Collectible* collects[MAX_COLLECTIBLES];
//    Music music;
//public:
//    Game()
//        : window(VideoMode(SCREEN_X, SCREEN_Y), "Sonic-OOP Improved"), curLevel(-1) {
//        window.setFramerateLimit(60);
//        music.openFromFile("../Data/labrynth.ogg");
//        music.setLoop(true);
//        music.play();
//        for (int i = 0; i < MAX_LEVELS; ++i)
//            levels[i] = new Level(i);
//        // Initialize enemies
//        enemies[0] = new BatBrain(300, 300);
//        enemies[1] = new BeeBot(500, 200);
//        enemies[2] = new Motobug(700, 300);
//        enemies[3] = new CrabMeat(900, 200);
//        enemies[4] = new EggStinger(1100, 100);
//        // Initialize collectibles
//        collects[0] = new Ring(400, 400);
//        collects[1] = new ExtraLife(600, 350);
//        collects[2] = new SpecialBoost(800, 400);
//        collects[3] = new Ring(1000, 300);
//        collects[4] = new Ring(200, 500);
//    }
//
//    ~Game() {
//        for (int i = 0; i < MAX_LEVELS; ++i) delete levels[i];
//        for (int i = 0; i < MAX_ENEMIES; ++i) delete enemies[i];
//        for (int i = 0; i < MAX_COLLECTIBLES; ++i) delete collects[i];
//    }
//
//    void run() {
//        Event ev;
//        Clock clock;
//        while (window.isOpen()) {
//            if (curLevel < 0) {
//                while (window.pollEvent(ev)) {
//                    if (ev.type == Event::Closed)
//                        window.close();
//                    int sel = menu.handleInput(ev);
//                    if (sel >= 0) {
//                        curLevel = sel;
//                        player.setLevel(levels[curLevel]); // aggregate level into player
//                        menu.reset();
//                    }
//                }
//                menu.draw(window);
//                continue;
//            }
//
//            float dt = clock.restart().asSeconds();
//            while (window.pollEvent(ev)) {
//                if (ev.type == Event::Closed)
//                    window.close();
//                if (ev.type == Event::KeyPressed) {
//                    if (ev.key.code == Keyboard::Tab)
//                        player.switchChar();
//                    if (ev.key.code == Keyboard::M)
//                        curLevel = -1;
//                }
//            }
//
//            // Update logic
//            player.update(dt);
//            for (int i = 0; i < MAX_ENEMIES; ++i)
//                enemies[i]->update(levels[curLevel]->grid, dt);
//            for (int j = 0; j < MAX_COLLECTIBLES; ++j)
//                collects[j]->update(dt);
//
//            // Draw logic with manual camera
//            window.clear();
//            float halfScreen = SCREEN_X / 2.f;
//            float levelWidth = LEVEL_WIDTH * CELL_SIZE;
//            float viewCenterX = player.getX() + CELL_SIZE / 2.f;
//            if (viewCenterX < halfScreen)
//                viewCenterX = halfScreen;
//            if (viewCenterX > levelWidth - halfScreen)
//                viewCenterX = levelWidth - halfScreen;
//            float offsetX = viewCenterX - halfScreen;
//
//            levels[curLevel]->draw(window, offsetX);
//            for (int i = 0; i < MAX_COLLECTIBLES; ++i)
//                collects[i]->draw(window, offsetX);
//            player.draw(window, offsetX);
//            for (int i = 0; i < MAX_ENEMIES; ++i)
//                enemies[i]->draw(window, offsetX);
//
//            window.display();
//        }
//    }
//};
//
//int main() {
//    Game game;
//    game.run();
//    return 0;
//}
