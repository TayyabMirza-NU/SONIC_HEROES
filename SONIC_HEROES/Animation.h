#pragma once
#include <SFML/Graphics.hpp>

// Single-file header-only Animation class
class Animation {
private:
    sf::Sprite sprite;
    sf::IntRect* frames{ nullptr };
    int frameCount{ 0 };
    int currentFrame{ 0 };
    float frameTime{ 0.1f };
    float elapsedTime{ 0.f };
    float scale{ 2.5f };

public:
    Animation() = default;
    ~Animation() { delete[] frames; }

    // Initialize the animation with a texture, frame width/height, number of frames, and time per frame
    void init(sf::Texture& tex, int fw, int fh, int count, float tpf) {
        delete[] frames;
        frameCount = count;
        frames = new sf::IntRect[count];
        frameTime = tpf;
        elapsedTime = 0.f;
        currentFrame = 0;

        // Split the texture into frames
        for (int i = 0; i < count; ++i) {
            frames[i] = sf::IntRect(i * fw, 0, fw, fh);
        }

        sprite.setTexture(tex);
        sprite.setTextureRect(frames[0]);
        sprite.setScale(scale, scale);
    }

    // Start (or restart) playback
    void play(bool ) {
        elapsedTime = 0.f;
        currentFrame = 0;
        if (frameCount > 0)
            sprite.setTextureRect(frames[0]);
    }

    // Stop and reset to first frame
    void stop() {
        elapsedTime = 0.f;
        currentFrame = 0;
        if (frameCount > 0)
            sprite.setTextureRect(frames[0]);
    }

    // Advance the animation by dt seconds
    void update(float dt) {
        if (frameCount <= 1) return;

        elapsedTime += dt;
        while (elapsedTime >= frameTime) {
            elapsedTime -= frameTime;
            currentFrame = (currentFrame + 1) % frameCount;
            sprite.setTextureRect(frames[currentFrame]);
        }
    }

    // Set the sprite position
    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    // Draw the sprite with an X-offset (e.g., for camera scrolling)
    void draw(sf::RenderWindow& win, float offsetX) {
        sf::Vector2f pos = sprite.getPosition();
        sprite.setPosition(pos.x + offsetX, pos.y);
        win.draw(sprite);
        sprite.setPosition(pos);
    }
};