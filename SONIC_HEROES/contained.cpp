//// contained.cpp
//
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <string>
//
//// Level dimensions
//const int CELL_SIZE = 32;
//const int LEVEL_W = 20;
//const int LEVEL_H = 7;
//
////----------------------------------------
//// Simple Animation for jump only
////----------------------------------------
//class JumpAnimation {
//public:
//    JumpAnimation() = default;
//    JumpAnimation(sf::Texture* framesArr, int count, float switchTime)
//        : frames(framesArr), frameCount(count), frameTime(switchTime)
//    {
//    }
//
//    void update(float dt) {
//        elapsed += dt;
//        if (elapsed >= frameTime) {
//            elapsed -= frameTime;
//            current = (current + 1) % frameCount;
//        }
//    }
//
//    void apply(sf::Sprite& spr) {
//        spr.setTexture(frames[current]);
//    }
//
//private:
//    sf::Texture* frames = nullptr;
//    int frameCount = 0;
//    float frameTime = 0.f;
//    int current = 0;
//    float elapsed = 0.f;
//};
//
////----------------------------------------
//// Player: movement, gravity, jump animation
////----------------------------------------
//class Player {
//public:
//    Player(sf::Texture& idleTex, sf::Texture* jumpFrames, int jumpCount,
//        float switchTime, float startX, float startY,
//        char** lvl, int lvlW, int lvlH)
//        : idleTexture(idleTex)
//        , jumpAnim(jumpFrames, jumpCount, switchTime)
//        , level(lvl), lvlWidth(lvlW), lvlHeight(lvlH)
//    {
//        sprite.setTexture(idleTexture);
//        sprite.setPosition(startX, startY);
//        width = idleTexture.getSize().x;
//        height = idleTexture.getSize().y;
//        onGround = false;
//        velX = velY = 0.f;
//        speed = 200.f;
//        gravity = 2000.f;
//        termVel = 1000.f;
//    }
//
//    void update(float dt) {
//        // horizontal input
//        velX = 0.f;
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  velX = -speed;
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) velX = speed;
//        sprite.move(velX * dt, 0);
//
//        // jump input
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround) {
//            velY = -600.f;
//            onGround = false;
//        }
//
//        // gravity
//        if (!onGround) {
//            velY += gravity * dt;
//            if (velY > termVel) velY = termVel;
//        }
//        float newY = sprite.getPosition().y + velY * dt;
//
//        // collision check downward
//        int xL = int(sprite.getPosition().x) / CELL_SIZE;
//        int xR = int(sprite.getPosition().x + width) / CELL_SIZE;
//        int yC = int(newY + height) / CELL_SIZE;
//        bool grounded = false;
//        if (yC >= 0 && yC < lvlHeight) {
//            if ((xL >= 0 && xL < lvlWidth && level[yC][xL] == 'w') ||
//                (xR >= 0 && xR < lvlWidth && level[yC][xR] == 'w')) {
//                grounded = true;
//                float snapY = yC * CELL_SIZE - height - 0.001f;
//                sprite.setPosition(sprite.getPosition().x, snapY);
//                velY = 0.f;
//            }
//        }
//        onGround = grounded;
//        if (!onGround) sprite.setPosition(sprite.getPosition().x, newY);
//
//        // animation: play jump when ascending
//        if (!onGround && velY < 0) {
//            jumpAnim.update(dt);
//            jumpAnim.apply(sprite);
//        }
//        else {
//            sprite.setTexture(idleTexture);
//        }
//    }
//
//    void draw(sf::RenderWindow& win) { win.draw(sprite); }
//
//private:
//    sf::Sprite sprite;
//    sf::Texture& idleTexture;
//    JumpAnimation jumpAnim;
//    float velX, velY;
//    float speed, gravity, termVel;
//    int width, height;
//    char** level;
//    int lvlWidth, lvlHeight;
//    bool onGround;
//};
//
////----------------------------------------
//// Main
////----------------------------------------
//int main() {
//    // NOTE: Ensure the game window is closed before rebuilding to avoid LNK1168
//    static char lvlData[LEVEL_H][LEVEL_W + 1] = {
//        "                    ",
//        "                    ",
//        "     w              ",
//        "    ww              ",
//        "   www      wwww    ",
//        "  wwwww            w",
//        "wwwwwwwwwwwwwwwwwwww"
//    };
//    static char* level[LEVEL_H];
//    for (int i = 0; i < LEVEL_H; ++i) level[i] = lvlData[i];
//
//    // load textures
//    sf::Texture idleTex;
//    if (!idleTex.loadFromFile("../Data/0left_still.png")) {
//        std::cerr << "Failed to load idle.png\n";
//        return -1;
//    }
//    const int JUMP_FRAMES = 4;
//    sf::Texture jumpFrames[JUMP_FRAMES];
//    for (int i = 0; i < JUMP_FRAMES; ++i) {
//        jumpFrames[i].loadFromFile("../Data/0upL.png");
//    }
//
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Jump Animate");
//    window.setFramerateLimit(60);
//
//    Player player(idleTex, jumpFrames, JUMP_FRAMES, 0.1f,
//        100.f, 100.f, level, LEVEL_W, LEVEL_H);
//
//    sf::Clock clk;
//    while (window.isOpen()) {
//        sf::Event e;
//        while (window.pollEvent(e)) {
//            if (e.type == sf::Event::Closed) window.close();
//            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
//                window.close();
//        }
//        float dt = clk.restart().asSeconds();
//        player.update(dt);
//
//        window.clear(sf::Color::Black);
//        for (int y = 0; y < LEVEL_H; ++y)
//            for (int x = 0; x < LEVEL_W; ++x)
//                if (level[y][x] == 'w') {
//                    sf::RectangleShape b(sf::Vector2f(CELL_SIZE, CELL_SIZE));
//                    b.setPosition(x * CELL_SIZE, y * CELL_SIZE);
//                    window.draw(b);
//                }
//        player.draw(window);
//        window.display();
//    }
//    return 0;
//}
