// Player.hpp
#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Player {
    Character* party[3];
    int activeIndex{ 0 };
public:
    Player() {
        party[0] = new Sonic();
        party[1] = new Tails();
        party[2] = new Knuckles();
    }
    ~Player() {
        for (int i = 0;i < 3;++i) delete party[i];
    }
    void init(const Texture textures[3]) {
        for (int i = 0;i < 3;++i) party[i]->init(const_cast<Texture&>(textures[i]));
    }
    void update(float dt) {
        if (Keyboard::isKeyPressed(Keyboard::Z)) {
            activeIndex = (activeIndex + 1) % 3;
            // simple debounce delay omitted
        }
        for (int i = 0;i < 3;++i) {
            if (i == activeIndex)
                party[i]->updateControl(dt);
            else
                party[i]->follow(party[activeIndex], dt);
        }
    }
    void render(RenderWindow& win, float offsetX = 0.f) {
        for (int i = 0;i < 3;++i)
            party[i]->render(win, offsetX);
    }
};