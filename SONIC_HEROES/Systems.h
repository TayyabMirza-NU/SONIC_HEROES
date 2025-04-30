// Systems.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include<iostream>
using namespace sf;
using namespace std;

class Menu {
private:
    static const int OPTION_COUNT = 4;
    Font font;
    Text options[OPTION_COUNT];
    int selected{ 0 };
    const char* labels[OPTION_COUNT] = { "Start Game", "Select Level", "Leaderboard", "Exit" };

public:
    Menu() {
        if (!font.loadFromFile("../Data/Jaro/Jaro.ttf"))
            std::cerr << "Failed to load Jato.ttf" << std::endl;
        for (int i = 0; i < OPTION_COUNT; ++i) {
            options[i] = Text(labels[i], font, 36);
            options[i].setPosition(100.f, 100.f + i * 60.f);
            options[i].setFillColor(i == selected ? Color::Yellow : Color::White);
        }
    }

    int navigate(const Event& ev) {
        if (ev.type == Event::KeyPressed) {
            if (ev.key.code == Keyboard::Up && selected > 0) selected--;
            if (ev.key.code == Keyboard::Down && selected + 1 < OPTION_COUNT) selected++;
            if (ev.key.code == Keyboard::Enter) return selected;
            for (int i = 0; i < OPTION_COUNT; ++i)
                options[i].setFillColor(i == selected ? Color::Yellow : Color::White);
        }
        return -1;
    }

    void draw(RenderWindow& win) {
        for (int i = 0; i < OPTION_COUNT; ++i)
            win.draw(options[i]);
    }
};

class SaveSystem {
private:
    std::string savePath;
public:
    void exportSave(int slot);
    void importSave(int slot);
};

class Leaderboard {
private:
    int topScores[GameConstants::MAX_TOP_SCORES];
    int scoreCount{ 0 };
public:
    void addScore(const std::string& name, int score);
    void getTop(int n);
};

class LevelManager {
private:
    int choice{ 1 };
    int maxLevels;
    Font font;
    Text prompt;
    Text* levelTexts;  // dynamic array

public:
    LevelManager(int maxLv)
        : maxLevels(maxLv)
    {
        if (!font.loadFromFile("../Data/Jaro/Jaro.ttf"))
            std::cerr << "Failed to load Jato.ttf" << std::endl;

        prompt = Text("Select Level (1-" + std::to_string(maxLevels) + ") and press Enter", font, 24);
        prompt.setPosition(50.f, 50.f);
        levelTexts = new Text[maxLevels];
        for (int i = 0; i < maxLevels; ++i) {
            levelTexts[i] = Text(std::to_string(i + 1), font, 30);
            levelTexts[i].setPosition(100.f + i * 80.f, 150.f);
        }
    }

    ~LevelManager() {
        delete[] levelTexts;
    }

    int navigate(const Event& ev) {
        if (ev.type == Event::KeyPressed) {
            if (ev.key.code == Keyboard::Left && choice > 1) choice--;
            if (ev.key.code == Keyboard::Right && choice < maxLevels) choice++;
            if (ev.key.code == Keyboard::Enter) return choice;
            for (int i = 0; i < maxLevels; ++i) {
                levelTexts[i].setFillColor((i + 1) == choice ? Color::Yellow : Color::White);
            }
        }
        return -1;
    }

    void draw(RenderWindow& win) {
        win.draw(prompt);
        for (int i = 0; i < maxLevels; ++i)
            win.draw(levelTexts[i]);
    }
};



class TileMap {
private:
    int cellWidth{ 0 }, cellHeight{ 0 };
public:
    char**& populate(char**& grid, int height, int width) {
        // 1. Clear entire grid first
        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                grid[i][j] = ' ';

        for (int j = 0; j < width; ++j)
            grid[height - 2][j] = 'w';

  
        for (int gap = 10; gap < width - 10; gap += 20) {
            for (int j = gap; j < gap + 4; ++j) {
                if (j < width)
                    grid[height - 2][j] = ' ';
            }
        }

  
        for (int j = 5; j < 15; ++j)
            grid[height - 6][j] = 'w'; 

        for (int j = 25; j < 35; ++j)
            grid[height - 8][j] = 'w'; 

        for (int j = 45; j < 50; ++j)
            grid[height - 5][j] = 'w'; 

        int stairStartX = 60;
        int stairStartY = height - 3;
        for (int step = 0; step < 5; ++step) {
            grid[stairStartY - step][stairStartX + step] = 'w';
        }

    
        int wallX = 80;
        for (int i = height - 3; i > height - 8; --i) {
            grid[i][wallX] = 'w';
        }

 
        for (int j = 95; j < 100; ++j)
            grid[height - 2][j] = ' ';

        int zzX = 105;
        int zzY = height - 3;
        for (int step = 0; step < 6; ++step) {
            grid[zzY - (step % 2)][zzX + step] = 'w';
        }

        return grid;
    }

    
};

class LevelTimer {
private:
    float timeLeft{ 0.f };
public:
    void update(float dt);
    bool isExpired() const;
};