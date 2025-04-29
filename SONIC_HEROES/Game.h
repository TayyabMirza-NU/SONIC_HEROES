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
using namespace std;

class Game {
private:
    static const int LEVEL_COUNT = 4;
    RenderWindow window;
    Level* levels;
    Player player;
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

        if (!gameMus.openFromFile("../Data/labrynth.ogg")) {
            cerr << "Failed to load music.\n";
        }
        else {
            gameMus.setVolume(30);
            gameMus.setLoop(true);
            gameMus.play();
        }

        levels = new Level[LEVEL_COUNT];
        for (int i = 0; i < LEVEL_COUNT; ++i)
            levels[i] = Level(i, 14, 110);
    }

    ~Game() {
        delete[] levels;
        window.close();
    }

    void run() {
        enum State { MENU, SELECT_LEVEL, PLAY, EXIT } state = MENU;
        int currentLevel = 0;

        Clock frameClock;

        while (window.isOpen() && state != EXIT) {
            Event ev;
            while (window.pollEvent(ev)) {
                if (ev.type == Event::Closed)
                    state = EXIT;

                if (state == MENU) {
                    int sel = menu.navigate(ev);
                    if (sel >= 0) {
                        switch (sel) {
                        case 0: state = PLAY; currentLevel = 0; break;
                        case 1: state = SELECT_LEVEL; break;
                        case 2: /* Leaderboard not implemented */ break;
                        case 3: state = EXIT; break;
                        }
                    }
                }
                else if (state == SELECT_LEVEL) {
                    int lvl = levelManager.navigate(ev);
                    if (lvl > 0 && lvl <= LEVEL_COUNT) {
                        currentLevel = lvl - 1;
                        state = PLAY;
                    }
                }
            }

            window.clear();

            switch (state) {
            case MENU:
                menu.draw(window);
                break;

            case SELECT_LEVEL:
                levelManager.draw(window);
                break;

            case PLAY: {
                // 1) Compute frame time
                float dt = frameClock.restart().asSeconds();
                if (dt > 0.05f) dt = 0.05f; // guard against large dt spikes

                // 2) Update level and player
                levels[currentLevel].update(dt);
                char** grid = levels[currentLevel].getGrid();
                player.update(grid, dt);

                // 3) Compute horizontal camera offset
                float halfW = GameConstants::SCREEN_X * 0.5f;
                float levelPixW = levels[currentLevel].getWidth() * GameConstants::CELL_SIZE;
                float playerCenterX = player.getX() + GameConstants::CELL_SIZE * 0.5f;

                // If level narrower than screen, lock at zero
                float offsetX;
                if (levelPixW <= GameConstants::SCREEN_X) {
                    offsetX = 0.f;
                }
                else {
                    float minCenter = halfW;
                    float maxCenter = levelPixW - halfW;
                    float viewCenter = std::clamp(playerCenterX, minCenter, maxCenter);
                    offsetX = viewCenter - halfW;
                }

                // 4) Render
                window.clear();
                levels[currentLevel].render(window, offsetX);
                player.draw(window, offsetX);
                break;
            }


            default:
                break;
            }

            window.display();
        }
    }
};
