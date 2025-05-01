#pragma once

#include <SFML/Graphics.hpp>

#include"Systems.h"

class Level {
    char** grid;
    TileMap map;
	sf::Sprite wallSprite;
	sf::Texture wallTex;

    int id;
    int width;
    int height;

public:
    Level() {
        if (!wallTex.loadFromFile("../Data/brick2.png")) {
            std::cerr << "ERROR: failed to load Data/brick1.png\n";
        }
        wallSprite.setTexture(wallTex);
    }
  
    void setLevel(int id,int l, int w){
		this->id = id;
        height = l;
        width = w;  
        grid = new char* [height];
        for (int i = 0; i < height; i++)
        {
            grid[i] = new char[width];
        }
    
		map.populate(grid, height, width);

    }
    void update(float dt) {

    }

    char**& getGrid() {
        return grid;
    }
	int getWidth() {
		return width;
	}

    void render(sf::RenderWindow& win, float offsetX) {
        // for each grid cell
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (grid[i][j] == 'w') {
                    wallSprite.setPosition(j * GameConstants::CELL_SIZE - offsetX, i * GameConstants::CELL_SIZE);
                    win.draw(wallSprite);
                }

            }
        }
    }
};




