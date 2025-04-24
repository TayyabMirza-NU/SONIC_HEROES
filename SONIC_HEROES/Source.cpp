//// ======================== Headers ========================
//#include <iostream>
//#include <vector>
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
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
//const int MAX_CHARACTERS = 3;
//const int MAX_ENEMIES = 5;
//const int MAX_COLLECTIBLES = 5;
//const int MAX_LEVELS = 4;
//
//// ======================== Animation ========================
//class Animation {
//private:
//    Sprite sprite;
//    vector<IntRect> frames;
//    int currentFrame;
//    float frameTime;
//    float elapsedTime;
//
//public:
//    Animation() : currentFrame(0), frameTime(0.1f), elapsedTime(0) {}
//
//    void init(Texture& tex, int frameWidth, int frameHeight, int count, float timePerFrame) {
//        sprite.setTexture(tex);
//        frames.clear();
//        for (int i = 0; i < count; ++i) {
//            frames.emplace_back(i * frameWidth, 0, frameWidth, frameHeight);
//        }
//        frameTime = timePerFrame;
//        currentFrame = 0;
//        sprite.setTextureRect(frames[0]);
//    }
//
//    void update(float dt) {
//        elapsedTime += dt;
//        if (elapsedTime >= frameTime) {
//            elapsedTime -= frameTime;
//            currentFrame = (currentFrame + 1) % frames.size();
//            sprite.setTextureRect(frames[currentFrame]);
//        }
//    }
//
//    void setPosition(float x, float y) {
//        sprite.setPosition(x, y);
//    }
//
//    void draw(RenderWindow& window) {
//        window.draw(sprite);
//    }
//};
//
//// ======================== Character Base ========================
//class Character {
//public:
//    void setPosition(float nx, float ny) { x = nx; y = ny; }
//    float getX() const { return x; }
//    float getY() const { return y; }
//
//protected:
//    float x, y;
//    float velocityX, velocityY;
//    bool onGround;
//    float gravity;
//    float terminalVelocity;
//    float moveSpeed;
//    int width, height;
//    int hitboxX, hitboxY;
//    Animation anim;
//    Texture texture;
//
//public:
//    Character()
//        : x(100), y(100), velocityX(0), velocityY(0), onGround(false),
//        gravity(1), terminalVelocity(20), moveSpeed(4.0f),
//        width(60), height(80), hitboxX(20), hitboxY(20)
//    {
//    }
//
//    virtual void loadAnimation(const string& path, int frameW, int frameH, int count, float timePerFrame) {
//        if (!texture.loadFromFile(path)) cerr << "Failed to load: " << path << endl;
//        anim.init(texture, frameW, frameH, count, timePerFrame);
//    }
//
//    virtual void handleInput() {
//        velocityX = 0;
//        if (Keyboard::isKeyPressed(Keyboard::A)) velocityX = -moveSpeed;
//        else if (Keyboard::isKeyPressed(Keyboard::D)) velocityX = moveSpeed;
//        if (Keyboard::isKeyPressed(Keyboard::Space) && onGround) {
//            velocityY = -20; onGround = false;
//        }
//    }
//
//    virtual void update(char** lvl, bool isControlled, float dt) {
//        if (isControlled) handleInput();
//        x += velocityX;
//        applyGravity(lvl);
//        anim.setPosition(x, y);
//        anim.update(dt);
//    }
//
//    void applyGravity(char** lvl) {
//        float nextY = y + velocityY;
//        int gridX = int(x + hitboxX + width / 2) / CELL_SIZE;
//        int gridY = int(nextY + hitboxY + height) / CELL_SIZE;
//        if (gridY < LEVEL_HEIGHT && gridX < LEVEL_WIDTH && lvl[gridY][gridX] == 'w') {
//            onGround = true; velocityY = 0;
//        }
//        else {
//            onGround = false; y = nextY;
//            velocityY += gravity;
//            if (velocityY > terminalVelocity) velocityY = terminalVelocity;
//        }
//    }
//
//    virtual void draw(RenderWindow& window) {
//        anim.draw(window);
//    }
//
//    void follow(Character* target, float offset) {
//        float dx = (target->getX() - offset) - x;
//        x += dx * 0.05f;
//    }
//};
//
//class Sonic : public Character { public: Sonic() { loadAnimation("../Data/0left_still.png", 24, 35, 1, 0.1f); } };
//class Tails : public Character { public: Tails() { loadAnimation("../Data/0left_still.png", 24, 35, 1, 0.1f); } };
//class Knuckles : public Character { public: Knuckles() { loadAnimation("../Data/0left_still.png", 24, 35, 1, 0.1f); } };
//
//// ======================== Enemy Base ========================
//class Enemy {
//protected:
//    float x, y;
//    Animation anim;
//    Texture texture;
//public:
//    Enemy(float sx = 0, float sy = 0) : x(sx), y(sy) {}
//    virtual void loadAnimation(const string& path, int fw, int fh, int cnt, float tpf) {
//        if (!texture.loadFromFile(path)) cerr << "Failed: " << path << endl;
//        anim.init(texture, fw, fh, cnt, tpf);
//    }
//    virtual void update(char** lvl, float dt) {
//        anim.setPosition(x, y);
//        anim.update(dt);
//    }
//    virtual void draw(RenderWindow& window) {
//        anim.draw(window);
//    }
//};
//class BatBrain : public Enemy { public: BatBrain(float sx, float sy) :Enemy(sx, sy) { loadAnimation("../Data/0left_still.png", 24, 35, 1, 0.1f); } };
//class BeeBot : public Enemy { public: BeeBot(float sx, float sy) :Enemy(sx, sy) { loadAnimation("../Data/0left_still.png", 24, 35, 1, 0.1f); } };
//class Motobug : public Enemy { public: Motobug(float sx, float sy) :Enemy(sx, sy) { loadAnimation("../Data/0left_still.png", 24, 35, 1, 0.1f); } };
//class CrabMeat : public Enemy { public: CrabMeat(float sx, float sy) :Enemy(sx, sy) { loadAnimation("../Data/0left_still.png", 24, 35, 1, 0.1f); } };
//class EggStinger : public Enemy { public: EggStinger(float sx, float sy) :Enemy(sx, sy) { loadAnimation("../Data/0left_still.png", 24, 35, 1, 0.1f); } };
//
//// ======================== Collectible Base ========================
//class Collectible {
//protected:
//    float x, y;
//    Animation anim;
//    Texture texture;
//public:
//    Collectible(float sx = 0, float sy = 0) : x(sx), y(sy) {}
//    virtual void loadAnimation(const string& path, int fw, int fh, int cnt, float tpf) {
//        if (!texture.loadFromFile(path)) cerr << "Failed: " << path << endl;
//        anim.init(texture, fw, fh, cnt, tpf);
//    }
//    virtual void applyEffect() {}
//    virtual void update(float dt) {
//        anim.setPosition(x, y);
//        anim.update(dt);
//    }
//    virtual void draw(RenderWindow& window) {
//        anim.draw(window);
//    }
//};
//class Ring : public Collectible { public: Ring(float sx, float sy) :Collectible(sx, sy) { loadAnimation("../Data/0left_still.png", 24, 35, 1, 0.1f); } };
//class ExtraLife : public Collectible { public: ExtraLife(float sx, float sy) :Collectible(sx, sy) { loadAnimation("../Data/0left_still.png", 24, 35, 1, 0.1f); } };
//class SpecialBoost : public Collectible { public: SpecialBoost(float sx, float sy) :Collectible(sx, sy) { loadAnimation("../Data/0left_still.png", 24, 35, 1, 0.1f); } };
//
//// ======================== Player ========================
//class Player {
//private:
//    Character* characters[MAX_CHARACTERS];
//    int currentIndex;
//public:
//    Player() : currentIndex(0) {
//        characters[0] = new Sonic();
//        characters[1] = new Tails();
//        characters[2] = new Knuckles();
//        characters[1]->setPosition(characters[0]->getX() - 80, characters[0]->getY());
//        characters[2]->setPosition(characters[0]->getX() - 160, characters[0]->getY());
//    }
//    ~Player() { for (int i = 0;i < MAX_CHARACTERS;++i) delete characters[i]; }
//    void switchChar() { currentIndex = (currentIndex + 1) % MAX_CHARACTERS; }
//    void update(char** lvl, float dt) {
//        characters[currentIndex]->update(lvl, true, dt);
//        for (int i = 0;i < MAX_CHARACTERS;++i) if (i != currentIndex) {
//            characters[i]->follow(characters[currentIndex], (i + 1) * 80);
//            characters[i]->update(lvl, false, dt);
//        }
//    }
//    void draw(RenderWindow& window) { for (int i = 0;i < MAX_CHARACTERS;++i) characters[i]->draw(window); }
//};
//
//// ======================== Level ========================
//class Level {
//private:
//    char** grid;
//    Texture wallTex;
//    Sprite wallSprite;
//public:
//    Level() {
//        grid = new char* [LEVEL_HEIGHT];
//        for (int i = 0;i < LEVEL_HEIGHT;++i) grid[i] = new char[LEVEL_WIDTH] {};
//        wallTex.loadFromFile("../Data/brick1.png");
//        wallSprite.setTexture(wallTex);
//        for (int j = 0;j < LEVEL_WIDTH;++j) grid[LEVEL_HEIGHT - 3][j] = 'w';
//    }
//    ~Level() { for (int i = 0;i < LEVEL_HEIGHT;++i) delete[] grid[i]; delete[] grid; }
//    char** getGrid() const { return grid; }
//    void draw(RenderWindow& window) {
//        for (int i = 0;i < LEVEL_HEIGHT;++i)
//            for (int j = 0;j < LEVEL_WIDTH;++j)
//                if (grid[i][j] == 'w') {
//                    wallSprite.setPosition(j * CELL_SIZE, i * CELL_SIZE);
//                    window.draw(wallSprite);
//                }
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
//        font.loadFromFile("../Data/Jaro/jaro.ttf");
//        title.setFont(font); title.setString("Sonic Classic Heroes"); title.setCharacterSize(48); title.setPosition(300, 100);
//        for (int i = 0;i < MAX_LEVELS;++i) {
//            options[i].setFont(font);
//            options[i].setString("Start Level " + to_string(i + 1));
//            options[i].setCharacterSize(32);
//            options[i].setPosition(400, 250 + i * 60);
//        }
//    }
//    int handleInput(const Event& ev) {
//        if (ev.type == Event::KeyPressed) {
//            if (ev.key.code == Keyboard::Up) selected = (selected + MAX_LEVELS - 1) % MAX_LEVELS;
//            else if (ev.key.code == Keyboard::Down) selected = (selected + 1) % MAX_LEVELS;
//            else if (ev.key.code == Keyboard::Enter) return selected;
//        }
//        return -1;
//    }
//    void draw(RenderWindow& window) {
//        window.clear(); window.draw(title);
//        for (int i = 0;i < MAX_LEVELS;++i) {
//            options[i].setFillColor(i == selected ? Color::Red : Color::White);
//            window.draw(options[i]);
//        }
//        window.display();
//    }
//};
//
//// ======================== Game ========================
//class Game {
//private:
//    RenderWindow window;
//    MenuScreen menu;
//    Level* levels[MAX_LEVELS];
//    int currentLevel;
//    Player player;
//    Enemy* enemies[MAX_ENEMIES];
//    Collectible* collectibles[MAX_COLLECTIBLES];
//    Music music;
//public:
//    Game()
//        : window(VideoMode(SCREEN_X, SCREEN_Y), "Sonic-OOP", Style::Close), currentLevel(-1)
//    {
//        window.setFramerateLimit(60);
//        music.openFromFile("../Data/labrynth.ogg"); music.setLoop(true); music.play();
//        for (int i = 0;i < MAX_LEVELS;++i) levels[i] = new Level();
//        enemies[0] = new BatBrain(300, 300); enemies[1] = new BeeBot(500, 200);
//        enemies[2] = new Motobug(700, 300); enemies[3] = new CrabMeat(900, 200);
//        enemies[4] = new EggStinger(1100, 100);
//        collectibles[0] = new Ring(400, 400); collectibles[1] = new ExtraLife(600, 350);
//        collectibles[2] = new SpecialBoost(800, 400); collectibles[3] = new Ring(1000, 300);
//        collectibles[4] = new Ring(200, 500);
//    }
//    ~Game() {
//        for (int i = 0;i < MAX_LEVELS;++i) delete levels[i];
//        for (int i = 0;i < MAX_ENEMIES;++i) delete enemies[i];
//        for (int j = 0;j < MAX_COLLECTIBLES;++j) delete collectibles[j];
//    }
//    void run() {
//        Event ev;
//        Clock clock;
//
//        while (window.isOpen()) {
//            if (currentLevel < 0) {
//                // ========== MENU MODE ==========
//                while (currentLevel < 0 && window.isOpen()) {
//                    while (window.pollEvent(ev)) {
//                        if (ev.type == Event::Closed) window.close();
//                        int sel = menu.handleInput(ev);
//                        if (sel >= 0) currentLevel = sel;
//                    }
//                    menu.draw(window);
//                }
//            }
//
//            // ========== GAME MODE ==========
//            float dt = clock.restart().asSeconds();
//            while (window.pollEvent(ev)) {
//                if (ev.type == Event::Closed) window.close();
//                if (ev.type == Event::KeyPressed) {
//                    if (ev.key.code == Keyboard::Tab) player.switchChar();
//                    if (ev.key.code == Keyboard::M) {
//                        currentLevel = -1; // triggers menu in next outer loop
//                    }
//                }
//            }
//
//            if (currentLevel < 0) continue;  // immediately jump to menu again
//
//            player.update(levels[currentLevel]->getGrid(), dt);
//            for (int i = 0; i < MAX_ENEMIES; ++i) enemies[i]->update(levels[currentLevel]->getGrid(), dt);
//            for (int j = 0; j < MAX_COLLECTIBLES; ++j) collectibles[j]->update(dt);
//
//            window.clear();
//            levels[currentLevel]->draw(window);
//            for (int j = 0; j < MAX_COLLECTIBLES; ++j) collectibles[j]->draw(window);
//            player.draw(window);
//            for (int i = 0; i < MAX_ENEMIES; ++i) enemies[i]->draw(window);
//            window.display();
//        }
//    }
//
//};
//
//int main() {
//    Game game;
//    game.run();
//    return 0;
//}






#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

// ======================== Constants ========================
const int SCREEN_X = 1200;
const int SCREEN_Y = 900;
const int CELL_SIZE = 64;
const int LEVEL_HEIGHT = 14;
const int LEVEL_WIDTH = 110;
const int MAX_LEVELS = 4;
const int MAX_ENEMIES = 5;
const int MAX_COLLECTIBLES = 5;
const int MAX_CHARACTERS = 3;
const int MAX_FRAMES = 10;

// ======================== Animation ========================
class Animation {
private:
    Sprite sprite;
    IntRect frames[MAX_FRAMES];
    int frameCount;
    int currentFrame;
    float frameTime;
    float elapsedTime;
    float scale;
public:
    Animation() :frameCount(0), currentFrame(0), frameTime(0.1f), elapsedTime(0),scale(2.5) {}
    void init(Texture& tex, int fw, int fh, int count, float tpf) {
        sprite.setTexture(tex);
        sprite.setScale(scale, scale);
        frameCount = count;
        for (int i = 0;i < count && i < MAX_FRAMES;++i) frames[i] = IntRect(i * fw, 0, fw, fh);
        frameTime = tpf;
        currentFrame = 0;
        elapsedTime = 0;
        sprite.setTextureRect(frames[0]);
    }
    void update(float dt) {
        elapsedTime += dt;
        if (elapsedTime >= frameTime && frameCount > 0) {
            elapsedTime -= frameTime;
            currentFrame = (currentFrame + 1) % frameCount;
            sprite.setTextureRect(frames[currentFrame]);
        }
    }
    void setPosition(float x, float y) { sprite.setPosition(x, y); }
    void draw(RenderWindow& win) { win.draw(sprite); }
};

// ======================== Platform ========================
class Platform {
public:
    bool checkCollision(const FloatRect& bbox) {
        // implement tile-based collision
        return false;
    }
};

class Character {
protected:
    float posX, posY;
    float velocityX, velocityY;
    bool isOnGround;
    float gravityAcceleration;
    float terminalVelocity;
    float movementSpeed;
    int spriteWidth, spriteHeight;
    int hitboxOffsetX, hitboxOffsetY;
    Animation anim;
public:
    Character()
        : posX(100.0f), posY(100.0f), velocityX(0.0f), velocityY(0.0f),
        isOnGround(false), gravityAcceleration(1.0f), terminalVelocity(20.0f), movementSpeed(4.0f),
        spriteWidth(24 * 2.5),
        spriteHeight(35 * 2.5),
        hitboxOffsetX(8 * 2.5),
        hitboxOffsetY(2 * 2.5)
    {
    }


    

    // Handle left/right/jump input
    virtual void handleInput() {
        velocityX = 0.0f;
        if (Keyboard::isKeyPressed(Keyboard::A))
            velocityX = -movementSpeed;
        else if (Keyboard::isKeyPressed(Keyboard::D))
            velocityX = movementSpeed;

        if (Keyboard::isKeyPressed(Keyboard::Space) && isOnGround) {
            velocityY = -20.0f;
            isOnGround = false;
        }
    }

 
    virtual void update(char** levelGrid, bool isControlled, float deltaTime) {
        // Input-driven horizontal velocity
        if (isControlled)
            handleInput();

        // Apply horizontal movement
        posX += velocityX;

        // Compute proposed vertical position
        float nextY = posY + velocityY;

        // Determine foot positions for collision (bottom-left & bottom-right)
        float leftFootX = posX + hitboxOffsetX;
        float rightFootX = posX + spriteWidth - hitboxOffsetX;
        // Adjust foot Y based on hitbox offset
        float footY = nextY + spriteHeight - hitboxOffsetY;

        int colLeft = static_cast<int>(leftFootX / CELL_SIZE);
        int colRight = static_cast<int>(rightFootX / CELL_SIZE);
        int row = static_cast<int>(footY / CELL_SIZE);

        bool onFloor = false;
        if (row >= 0 && row < LEVEL_HEIGHT) {
            if (colLeft >= 0 && colLeft < LEVEL_WIDTH && levelGrid[row][colLeft] == 'w') onFloor = true;
            if (colRight >= 0 && colRight < LEVEL_WIDTH && levelGrid[row][colRight] == 'w') onFloor = true;
        }

        if (onFloor) {
            // Snap to the top of the floor tile
            isOnGround = true;
            velocityY = 0.0f;
            posY = row * CELL_SIZE - (spriteHeight - hitboxOffsetY);
        }
        else {
            isOnGround = false;
            posY = nextY;
            // Gravity
            velocityY += gravityAcceleration;
            if (velocityY > terminalVelocity)
                velocityY = terminalVelocity;
        }

        // Update animation's position and frame
        anim.setPosition(posX, posY);
        anim.update(deltaTime);
    }
    int getX()const {
        return posX;
    }
    // Draw current animation frame
    virtual void draw(RenderWindow& window) {
        anim.draw(window);
    }
};

class Sonic : public Character {
private:
    Animation stillL, stillR;
    Animation walkLeft, walkRight;
    Animation runLeft, runRight;
    Animation attackLeft, attackRight;
    Animation* currentAnim;
    Texture texStillL, texStillR;
    Texture texWalkLeft, texWalkRight;
    Texture texRunLeft, texRunRight;
    Texture texAttackLeft, texAttackRight;
public:
    Sonic() {
        // Load animations
        texStillL.loadFromFile("../Data/0left_Still.png");
        stillL.init(texStillL, 40, 35, 1, 0.0f);
        texStillR.loadFromFile("../Data/0right_Still.png");
        stillR.init(texStillR, 40, 35, 1, 0.0f);
        texWalkLeft.loadFromFile("../Data/0jog_left.png");
        walkLeft.init(texWalkLeft, 40, 35, 4, 0.1f);
        texWalkRight.loadFromFile("../Data/0jog_right.png");
        walkRight.init(texWalkRight, 40, 35, 4, 0.1f);
        texRunLeft.loadFromFile("../Data/0left_run.png");
        runLeft.init(texRunLeft, 40, 35, 6, 0.08f);
        texRunRight.loadFromFile("../Data/0right_run.png");
        runRight.init(texRunRight, 40, 35, 6, 0.08f);
        texAttackLeft.loadFromFile("../Data/0upL.png");
        attackLeft.init(texAttackLeft, 40, 35, 3, 0.12f);
        texAttackRight.loadFromFile("../Data/0upR.png");
        attackRight.init(texAttackRight, 40, 35, 3, 0.12f);
        // Default animation state
        currentAnim = &stillR;
    }

    // Only handle movement input here
    void handleInput() override {
        velocityX = 0.0f;
        if (Keyboard::isKeyPressed(Keyboard::A))
            velocityX = -movementSpeed;
        else if (Keyboard::isKeyPressed(Keyboard::D))
            velocityX = movementSpeed;
        if (Keyboard::isKeyPressed(Keyboard::Space) && isOnGround) {
            velocityY = -20.0f;
            isOnGround = false;
        }
    }

    // Update physics & select animation after physics
    void update(char** levelGrid, bool isControlled, float deltaTime) override {
        if (isControlled)
            handleInput();
        Character::update(levelGrid, isControlled, deltaTime);
        // Select animation based on state
        if (!isOnGround) {
            currentAnim = (velocityX < 0 ? &attackLeft : &attackRight);
        }
        else if (velocityX < 0) {
            currentAnim = (fabs(velocityX) > movementSpeed * 0.5f ? &runLeft : &walkLeft);
        }
        else if (velocityX > 0) {
            currentAnim = (fabs(velocityX) > movementSpeed * 0.5f ? &runRight : &walkRight);
        }
        else {
            currentAnim = (currentAnim == &walkLeft || currentAnim == &runLeft || currentAnim == &attackLeft)
                ? &stillL : &stillR;
        }
        currentAnim->setPosition(posX, posY);
        currentAnim->update(deltaTime);
    }

    void draw(RenderWindow& win) override {
        currentAnim->draw(win);
    }
};
class Tails : public Character { };
class Knuckles : public Character {  };

// ======================== Enemy Hierarchy ========================
class Enemy {
protected:
    float x, y;
    Animation anim;
    Texture tex;
public:
    Enemy(float sx = 0, float sy = 0) :x(sx), y(sy) {}
    virtual void load(const string& path) { tex.loadFromFile(path); anim.init(tex, 24, 35, 1, 0.1f); }
    virtual void update(char** lvl, float dt) { anim.setPosition(x, y); anim.update(dt); }
    virtual void draw(RenderWindow& win) { anim.draw(win); }
};
class BatBrain : public Enemy { public: BatBrain(float sx, float sy) :Enemy(sx, sy) { load("../Data/0left_still.png"); } };
class BeeBot : public Enemy { public: BeeBot(float sx, float sy) :Enemy(sx, sy) { load("../Data/0left_still.png"); } };
class Motobug : public Enemy { public: Motobug(float sx, float sy) :Enemy(sx, sy) { load("../Data/0left_still.png"); } };
class CrabMeat : public Enemy { public: CrabMeat(float sx, float sy) :Enemy(sx, sy) { load("../Data/0left_still.png"); } };
class EggStinger : public Enemy { public: EggStinger(float sx, float sy) :Enemy(sx, sy) { load("../Data/0left_still.png"); } };

// ======================== Collectible Hierarchy ========================
class Collectible {
protected:
    float x, y;
    Animation anim;
    Texture tex;
public:
    Collectible(float sx = 0, float sy = 0) :x(sx), y(sy) {}
    virtual void load(const string& path) { tex.loadFromFile(path); anim.init(tex, 24, 35, 1, 0.1f); }
    virtual void applyEffect(Character* c) {}
    virtual void update(float dt) { anim.setPosition(x, y); anim.update(dt); }
    virtual void draw(RenderWindow& win) { anim.draw(win); }
};
class Ring : public Collectible { public: Ring(float sx, float sy) :Collectible(sx, sy) { load("../Data/0left_still.png"); } void applyEffect(Character* c) override {} };
class ExtraLife : public Collectible { public: ExtraLife(float sx, float sy) :Collectible(sx, sy) { load("../Data/0left_still.png"); } void applyEffect(Character* c) override {} };
class SpecialBoost : public Collectible { public: SpecialBoost(float sx, float sy) :Collectible(sx, sy) { load("../Data/0left_still.png"); } void applyEffect(Character* c) override {} };

// ======================== Player ========================
class Player {
private:
    Character* chars[MAX_CHARACTERS];
    int idx;
public:
    Player() :idx(0) { chars[0] = new Sonic(); chars[1] = new Tails(); chars[2] = new Knuckles(); }
    void switchChar() { idx = (idx + 1) % MAX_CHARACTERS; }
    void update(char** lvl, float dt) { chars[idx]->update(lvl, true, dt); }
    void draw(RenderWindow& win) { chars[idx]->draw(win); }
    int getX()const {
        return chars[idx]->getX();
    }
};

// ======================== Level ========================
class Level {
public:
    char** grid;
    Texture wallTex;
    Sprite wallSprite;
    Level() {
        grid = new char* [LEVEL_HEIGHT];
        for (int i = 0;i < LEVEL_HEIGHT;++i) grid[i] = new char[LEVEL_WIDTH] {};
        wallTex.loadFromFile("../Data/brick1.png");
        wallSprite.setTexture(wallTex);
        for (int j = 0;j < LEVEL_WIDTH;++j) grid[LEVEL_HEIGHT - 3][j] = 'w';
    }
    ~Level() {
        for (int i = 0;i < LEVEL_HEIGHT;++i) delete[] grid[i];
        delete[] grid;
    }
    void draw(RenderWindow& win) {
        for (int i = 0;i < LEVEL_HEIGHT;++i)
            for (int j = 0;j < LEVEL_WIDTH;++j)
                if (grid[i][j] == 'w') {
                    wallSprite.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                    win.draw(wallSprite);
                }
    }
};

// ======================== Menu, SaveManager, Leaderboard ========================
class MenuScreen { public: int handleInput(const Event& ev) { if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Enter) return 0; return -1; } void draw(RenderWindow& win) { win.clear(); /* draw UI */ win.display(); } };
class SaveManager { public: void saveGame() {} void loadGame() {} };
class Leaderboard { public: void addScore(const string&, int) {} void getTopScores(int outScores[], int& count) { count = 0; } };

                          // ======================== Game ========================
                          class Game {
                          private:
                              RenderWindow window;
                              MenuScreen menu;
                              Level* levels[MAX_LEVELS];
                              int curLevel;
                              Player player;
                              Enemy* enemies[MAX_ENEMIES];
                              Collectible* collects[MAX_COLLECTIBLES];
                              Music music;
                          public:
                              Game() :window(VideoMode(SCREEN_X, SCREEN_Y), "Sonic-OOP"), curLevel(-1) {
                                  View view(FloatRect(0, 0, SCREEN_X, SCREEN_Y));
                                  window.setView(view);
                                  window.setFramerateLimit(60);
                                  music.openFromFile("../Data/labrynth.ogg"); music.setLoop(true); music.play();
                                  for (int i = 0;i < MAX_LEVELS;++i) levels[i] = new Level();
                                  enemies[0] = new BatBrain(300, 300); enemies[1] = new BeeBot(500, 200);
                                  enemies[2] = new Motobug(700, 300); enemies[3] = new CrabMeat(900, 200);
                                  enemies[4] = new EggStinger(1100, 100);
                                  collects[0] = new Ring(400, 400); collects[1] = new ExtraLife(600, 350);
                                  collects[2] = new SpecialBoost(800, 400); collects[3] = new Ring(1000, 300);
                                  collects[4] = new Ring(200, 500);
                              }
                              void run() {
                                  Event ev; Clock clock;
                                  while (window.isOpen()) {
                                      if (curLevel < 0) {
                                          while (window.pollEvent(ev)) { if (ev.type == Event::Closed) window.close(); int s = menu.handleInput(ev); if (s >= 0) curLevel = s; }
                                          menu.draw(window);
                                          continue;
                                      }
                                      float dt = clock.restart().asSeconds();
                                      while (window.pollEvent(ev)) {
                                          if (ev.type == Event::Closed) window.close();
                                          if (ev.type == Event::KeyPressed) {
                                              if (ev.key.code == Keyboard::Tab) player.switchChar();
                                              if (ev.key.code == Keyboard::M) curLevel = -1;
                                          }
                                      }
                                      player.update(levels[curLevel]->grid, dt);
                                      for (int i = 0;i < MAX_ENEMIES;++i) enemies[i]->update(levels[curLevel]->grid, dt);
                                      for (int j = 0;j < MAX_COLLECTIBLES;++j) collects[j]->update(dt);
                                      window.clear(); levels[curLevel]->draw(window);
                                      for (int j = 0;j < MAX_COLLECTIBLES;++j) collects[j]->draw(window);
                                      player.draw(window);
                                      for (int i = 0;i < MAX_ENEMIES;++i) enemies[i]->draw(window);
                                      // --- View clamping logic ---
                                      View view = window.getView();
                                      float halfScreen = SCREEN_X / 2.0f;
                                      float levelPixelWidth = LEVEL_WIDTH * CELL_SIZE;

                                      float viewCenterX = player.getX() + 0.5f * CELL_SIZE;

                                      if (viewCenterX < halfScreen) viewCenterX = halfScreen;
                                      if (viewCenterX > levelPixelWidth - halfScreen) viewCenterX = levelPixelWidth - halfScreen;

                                      view.setCenter(viewCenterX, SCREEN_Y / 2.0f);
                                      window.setView(view);

                                      window.display();
                                  }
                              }
                          };

                          int main() { Game game; game.run(); return 0; }


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
//int screen_x = 1200;
//int screen_y = 900;
//
//// prototypes 
//void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth);
//
//void draw_player(RenderWindow& window, Sprite& LstillSprite, float player_x, float player_y);
//
//void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite& wallSprite1, const int cell_size);
//
//int main()
//{
//
//	RenderWindow window(VideoMode(screen_x, screen_y), "Sonic the Hedgehog-OOP", Style::Close);
//	window.setVerticalSyncEnabled(true);
//	window.setFramerateLimit(60);
//	/////////////////////////////////////////////////////////////////
//	// a cell is 64 by 64 pixels
//
//	// 's' is regular space
//	// 'q' is wall1 or floor1
//	// 'w' is wall2 or floor2
//	// 'e' is wall3 or floor3
//	// 'b' is breakable wall
//	// 'z' is spring
//
//	// Uppercase for not interactable background accessories
//
//	// C is for crystals
//
//	const int cell_size = 64;
//	const int height = 14;
//	const int width = 110;
//
//	char** lvl = NULL;
//
//	Texture wallTex1;
//	Sprite wallSprite1;
//
//	Music lvlMus;
//
//	lvlMus.openFromFile("../Data/labrynth.ogg");
//	lvlMus.setVolume(30);
//	lvlMus.play();
//	lvlMus.setLoop(true);
//
//	lvl = new char* [height];
//	for (int i = 0; i < height; i += 1)
//	{
//		lvl[i] = new char[width] {'\0'};
//	}
//
//
//	lvl[11][1] = 'w';
//	lvl[11][2] = 'w';
//	lvl[11][3] = 'w';
//
//	wallTex1.loadFromFile("../Data/brick1.png");
//	wallSprite1.setTexture(wallTex1);
//	////////////////////////////////////////////////////////
//	float player_x = 100;
//	float player_y = 100;
//
//	float max_speed = 15;
//
//	float velocityX = 0;
//	float velocityY = 0;
//
//	float jumpStrength = -20; // Initial jump velocity
//	float gravity = 1;  // Gravity acceleration
//
//	Texture LstillTex;
//	Sprite LstillSprite;
//
//	bool onGround = false;
//
//	float offset_x = 0;
//	float offset_y = 0;
//
//	float terminal_Velocity = 20;
//
//	float acceleration = 0.2;
//
//	float scale_x = 2.5;
//	float scale_y = 2.5;
//
//	////////////////////////////
//	int raw_img_x = 24;
//	int raw_img_y = 35;
//
//	int Pheight = raw_img_y * scale_y;
//	int Pwidth = raw_img_x * scale_x;
//
//	//only to adjust the player's hitbox
//
//	int hit_box_factor_x = 8 * scale_x;
//	int hit_box_factor_y = 5 * scale_y;
//
//	LstillTex.loadFromFile("../Data/0left_still.png");
//	LstillSprite.setTexture(LstillTex);
//	LstillSprite.setScale(scale_x, scale_y);
//
//	////////////////////////////////////////////////////////
//
//	Event ev;
//	while (window.isOpen())
//	{
//
//		while (window.pollEvent(ev))
//		{
//			if (ev.type == Event::Closed)
//			{
//				window.close();
//			}
//
//			if (ev.type == Event::KeyPressed)
//			{
//			}
//
//		}
//
//		if (Keyboard::isKeyPressed(Keyboard::Escape))
//		{
//			window.close();
//		}
//
//		player_gravity(lvl, offset_y, velocityY, onGround, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, player_x, player_y, cell_size, Pheight, Pwidth);
//
//		window.clear();
//
//		display_level(window, height, width, lvl, wallSprite1, cell_size);
//		draw_player(window, LstillSprite, player_x, player_y);
//
//		window.display();
//	}
//
//
//	return 0;
//}
//
//
//// functions
//
//void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth)
//{
//	offset_y = player_y;
//
//	offset_y += velocityY;
//
//	char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x) / cell_size];
//	char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth) / cell_size];
//	char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size];
//
//
//	if (bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w')
//	{
//		onGround = true;
//	}
//	else
//	{
//		player_y = offset_y;
//		onGround = false;
//	}
//
//	if (!onGround)
//	{
//		velocityY += gravity;
//		if (velocityY >= terminal_Velocity) velocityY = terminal_Velocity;
//	}
//
//	else
//	{
//		velocityY = 0;
//	}
//
//}
//void draw_player(RenderWindow& window, Sprite& LstillSprite, float player_x, float player_y) {
//
//	LstillSprite.setPosition(player_x, player_y);
//	window.draw(LstillSprite);
//
//}
//void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite& wallSprite1, const int cell_size)
//{
//	for (int i = 0; i < height; i += 1)
//	{
//		for (int j = 0; j < width; j += 1)
//		{
//			if (lvl[i][j] == 'w')
//			{
//				wallSprite1.setPosition(j * cell_size, i * cell_size);
//				window.draw(wallSprite1);
//			}
//		}
//	}
//}