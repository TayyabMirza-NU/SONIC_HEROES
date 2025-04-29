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
    Level() {}
    Level(int id,int l, int w):id(id),height(l), width(w){
        if (!wallTex.loadFromFile("../Data/brick1.png")) {
            std::cerr << "ERROR: failed to load Data/brick1.png\n";
        }
        wallSprite.setTexture(wallTex);
        

		
        
        grid = new char* [height];
        for (int i = 0; i < height; i++)
        {
            grid[i] = new char[width];
        }
       /* grid = map.populate(grid, height, width);*/
       /* for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++) {
				std::cout << grid[i][j] << " ";
            }
            std::cout << endl;
        }*/
		grid = map.populate(grid, height, width);

    }
    void update(float dt) {
        // Update logic for the level


    }

    char** getGrid() {
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
                    wallSprite.setPosition(
                        j * GameConstants::CELL_SIZE - offsetX,
                        i * GameConstants::CELL_SIZE
                    );
                    win.draw(wallSprite);
                }

            }
        }
    }
};




//class Level {
//        int id;
//        int LEVEL_WIDTH;
//        int LEVEL_HEIGHT;
//public:
//    char** grid;
//    Texture wallTex;
//    Sprite wallSprite;
//    Level(){}
//    Level(int num, int height, int width) {
//
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
//        char** getGrid() {
//        return grid;
//    }
//
//    ~Level() { for (int i = 0;i < LEVEL_HEIGHT;++i) delete[] grid[i]; delete[] grid; }
//    void render(RenderWindow& win, float offsetX) {
//        for (int i = 0;i < LEVEL_HEIGHT;++i) 
//            for (int j = 0;j < LEVEL_WIDTH;++j) 
//                if (grid[i][j] == 'w') {
//            wallSprite.setPosition(j * GameConstants::CELL_SIZE - offsetX, i * GameConstants::CELL_SIZE);
//            win.draw(wallSprite);
//        }
//    }
//};