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
public:
    Animation() :frameCount(0), currentFrame(0), frameTime(0.1f), elapsedTime(0) {}
    void init(Texture& tex, int fw, int fh, int count, float tpf) {
        sprite.setTexture(tex);
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

// ======================== Character Hierarchy ========================
class Character {
protected:
    float x, y;
    float vx, vy;
    bool onGround;
    float gravity, termVel, moveSpeed;
    int width, height, hitX, hitY;
    Animation anim;
    Texture tex;
public:
    Character() :x(100), y(100), vx(0), vy(0), onGround(false), gravity(1), termVel(20), moveSpeed(4), width(24), height(35), hitX(8), hitY(5) {}
    virtual void load(const string& path) {
        tex.loadFromFile(path);
        anim.init(tex, width, height, 1, 0.1f);
    }
    virtual void handleInput() {
        vx = 0;
        if (Keyboard::isKeyPressed(Keyboard::A)) vx = -moveSpeed;
        else if (Keyboard::isKeyPressed(Keyboard::D)) vx = moveSpeed;
        if (Keyboard::isKeyPressed(Keyboard::Space) && onGround) { vy = -20; onGround = false; }
    }
    virtual void update(char** lvl, bool ctrl, float dt) {
        if (ctrl) handleInput();
        x += vx;
        float ny = y + vy;
        int gx = int((x + hitX + width / 2) / CELL_SIZE);
        int gy = int((ny + hitY + height) / CELL_SIZE);
        if (gy < LEVEL_HEIGHT && gx < LEVEL_WIDTH && lvl[gy][gx] == 'w') {
            onGround = true; vy = 0;
        }
        else {
            onGround = false; y = ny;
            vy += gravity;
            if (vy > termVel) vy = termVel;
        }
        anim.setPosition(x, y);
        anim.update(dt);
    }
    virtual void draw(RenderWindow& win) { anim.draw(win); }
};
class Sonic : public Character { public: Sonic() { load("../Data/0left_still.png"); } };
class Tails : public Character { public: Tails() { load("../Data/0left_still.png"); } };
class Knuckles : public Character { public: Knuckles() { load("../Data/0left_still.png"); } };

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
                                      window.display();
                                  }
                              }
                          };

                          int main() { Game game; game.run(); return 0; }
