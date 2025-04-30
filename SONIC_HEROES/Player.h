// Player.hpp
#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Player {
private:
    Character* chars[3];
    int idx;
public:
    Player() :idx(0) { 
        chars[0] = new Sonic(); 
        chars[1] = new Sonic(); 
        chars[2] = new Sonic(); 
    }
    void switchChar() { 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
            idx = (idx + 1) % 3; 
        }
    }
    void update(char** lvl, float dt) { 
        chars[idx]->update(lvl, true, dt); 
    }
    void draw(RenderWindow& win, float offsetX) { 
        chars[idx]->draw(win, offsetX); 
    }
    int getX() const { 
        return chars[idx]->getX(); 
    }
};