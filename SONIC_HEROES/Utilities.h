
#pragma once
#include <SFML/Graphics.hpp>

//struct Hitbox {
//    float width{ 0 }, height{ 0 };
//    Hitbox() = default;
//    Hitbox(float w, float h) : width(w), height(h) {}
//    bool checkCollision(const Hitbox& other) const {
//        return (width > 0 && height > 0 && other.width > 0 && other.height > 0);
//    }
//};
inline void player_gravity(char** lvl,
    int levelHeight, int levelWidth,
    float& offset_y, float& velocityY, bool& onGround,
    float gravity, float terminal_Velocity,
    int hit_box_fx, int hit_box_fy,
    float& player_x, float& player_y,
    int cell_size, int Pheight, int Pwidth)
{
    offset_y = player_y + velocityY;
    int row0 = static_cast<int>((offset_y + hit_box_fy + Pheight) / cell_size);
    if (row0 < 0) row0 = 0;
    if (row0 >= levelHeight) row0 = levelHeight - 1;

    int colL = static_cast<int>((player_x + hit_box_fx) / cell_size);
    int colR = static_cast<int>((player_x + hit_box_fx + Pwidth) / cell_size);
    int colM = static_cast<int>((player_x + hit_box_fx + Pwidth / 2) / cell_size);
    if (colL < 0) colL = 0; if (colL >= levelWidth) colL = levelWidth - 1;
    if (colR < 0) colR = 0; if (colR >= levelWidth) colR = levelWidth - 1;
    if (colM < 0) colM = 0; if (colM >= levelWidth) colM = levelWidth - 1;

    char bl = lvl[row0][colL];
    char bm = lvl[row0][colM];
    char br = lvl[row0][colR];

    if (bl == 'w' || bl == 'p' || bm == 'w' || bm == 'p' || br == 'w' || br == 'p') {
        onGround = true;
        velocityY = 0.f;
        player_y = row0 * cell_size - (Pheight + hit_box_fy);
    }
    else {
        onGround = false;
        player_y = offset_y;
        velocityY += gravity;
        if (velocityY > terminal_Velocity)
            velocityY = terminal_Velocity;
    }
}

inline void draw_player(sf::RenderWindow& window, sf::Sprite& sprite,
    float player_x, float player_y)
{
    sprite.setPosition(player_x, player_y);
    window.draw(sprite);
}

inline void display_level(sf::RenderWindow& window,
    int height, int width,
    char** lvl,
    sf::Sprite& wallSprite,
    sf::Sprite& platformSprite,
    int cell_size)
{
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            char tile = lvl[i][j];
            if (tile == 'w') {
                wallSprite.setPosition(j * cell_size, i * cell_size);
                window.draw(wallSprite);
            }
            else if (tile == 'p') {
                platformSprite.setPosition(j * cell_size, i * cell_size);
                window.draw(platformSprite);
            }
        }
    }
}