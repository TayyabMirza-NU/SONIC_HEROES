//// Game.h
//#pragma once
//
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include "Constants.h"
//#include "Utilities.h"
//#include "Level.h"
//#include "Player.h"
//#include "Systems.h"
//#include <iostream>
//
//using namespace sf;
//
//class Game {
//private:
//    static const int LEVEL_COUNT = 4;
//    RenderWindow window;
//    Level* levels;       // dynamic array
//    Player* player;
//    Music gameMus;
//    Menu menu;
//    LevelManager levelManager;
//
//public:
//    Game()
//        : window(VideoMode(GameConstants::SCREEN_X, GameConstants::SCREEN_Y), "Sonic the Hedgehog-OOP"),
//        levelManager(LEVEL_COUNT)
//    {
//        window.setVerticalSyncEnabled(true);
//        window.setFramerateLimit(60);
//        if (!gameMus.openFromFile("Data/labrynth.ogg"))
//            std::cerr << "Failed to load music" << std::endl;
//        gameMus.setVolume(30);
//        gameMus.setLoop(true);
//        gameMus.play();
//
//        levels = new Level[LEVEL_COUNT];
//        for (int i = 0; i < LEVEL_COUNT; ++i)
//            levels[i] = Level(14, 110);
//
//        player = new Player();
//    }
//
//    ~Game() {
//        delete[] levels;
//        delete player;
//        window.close();
//    }
//
//    void run() {
//        enum State { MENU, SELECT_LEVEL, PLAY, EXIT } state = MENU;
//        int currentLevel = 0;
//
//        while (window.isOpen() && state != EXIT) {
//            Event ev;
//            while (window.pollEvent(ev)) {
//                if (ev.type == Event::Closed)
//                    state = EXIT;
//
//                if (state == MENU) {
//                    int sel = menu.navigate(ev);
//                    if (sel >= 0) {
//                        switch (sel) {
//                        case 0: state = PLAY; currentLevel = 0; break;
//                        case 1: state = SELECT_LEVEL; break;
//                        case 2: /* leaderboard not implemented */ break;
//                        case 3: state = EXIT; break;
//                        }
//                    }
//                }
//                else if (state == SELECT_LEVEL) {
//                    int lvl = levelManager.navigate(ev);
//                    if (lvl > 0 && lvl<4) { currentLevel = lvl - 1; state = PLAY; }
//                }
//            }
//
//            window.clear();
//            switch (state) {
//            case MENU:            menu.draw(window);                  break;
//            case SELECT_LEVEL:    levelManager.draw(window);        break;
//            case PLAY: {
//                float dt = 1.f / 60.f;
//                levels[currentLevel].update(dt);
//                player->update(dt);
//                levels[currentLevel].render(window);
//                player->render(window);
//            } break;
//            default: break;
//            }
//            window.display();
//        }
//    }
//};
//
//
//
//
//


#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Utilities.h"
#include "Level.h"
#include "Player.h"
#include "Systems.h"
#include <iostream>

using namespace sf;

class Game {
    static const int LEVEL_COUNT = 4;
    RenderWindow window;
    Level* levels;
    Player player;
    Texture charTextures[3];
    Music gameMus;
    Menu menu;
    LevelManager levelManager;
public:
    Game()
        : window(VideoMode(GameConstants::SCREEN_X, GameConstants::SCREEN_Y), "Sonic Heroes OOP"),
        levelManager(LEVEL_COUNT)
    {
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);
        if (!gameMus.openFromFile("../Data/labrynth.ogg"))
            std::cerr << "Music load failed" << std::endl;
        gameMus.setVolume(30); gameMus.setLoop(true); gameMus.play();

        levels = new Level[LEVEL_COUNT];
        for (int i = 0;i < LEVEL_COUNT;++i)
            levels[i] = Level(14, 110);

        // load character textures
        charTextures[0].loadFromFile("../Data/0left_still.png");
        charTextures[1].loadFromFile("../Data/tails.png");
        charTextures[2].loadFromFile("../Data/knuckles.png");
        player.init(charTextures);
    }
    ~Game() {
        delete[] levels;
        window.close();
    }
    void run() {
        enum State { MENU, SELECT_LEVEL, PLAY, EXIT } state = MENU;
        int currentLevel = 0;
        sf::Clock switchClock;
        while (window.isOpen() && state != EXIT) {
            Event ev;
            while (window.pollEvent(ev)) {
                if (ev.type == Event::Closed) state = EXIT;
                if (state == PLAY) player.update(1.f / 60.f);
                if (state == MENU) {
                    int sel = menu.navigate(ev);
                    if (sel >= 0) {
                        switch (sel) {
                        case 0: state = PLAY; currentLevel = 0; break;
                        case 1: state = SELECT_LEVEL; break;
                        case 2: /* leaderboard not implemented */ break;
                        case 3: state = EXIT; break;
                        }
                    }
                }
                else if (state == SELECT_LEVEL) {
                    int lvl = levelManager.navigate(ev);
                    if (lvl > 0 && lvl < 4) { currentLevel = lvl - 1; state = PLAY; }
                }
            }
            window.clear();
            switch (state) {
            case MENU: menu.draw(window); break;
            case SELECT_LEVEL: levelManager.draw(window); break;
            case PLAY:
                levels[currentLevel].update(1.f / 60.f);
                levels[currentLevel].render(window);
                player.render(window);
                break;
            default: break;
            }
            window.display();
        }
    }
};
