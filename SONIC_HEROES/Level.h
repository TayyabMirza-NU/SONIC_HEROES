// Level.hpp
#pragma once

#include <SFML/Graphics.hpp>

class Level {
public:
	char** grid;
    Level() {}
    int id;
    std::string name;
    int width;
    int height;
	Level(int l, int w) {

		
	}
    void update(float dt) {
		// Update logic for the level

         
    }
    void render(sf::RenderWindow& win) {
		// Render logic for the level
    }
};
