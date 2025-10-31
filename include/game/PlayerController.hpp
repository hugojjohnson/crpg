#pragma once
#include <SFML/Graphics.hpp>
#include "../common/TileManager.hpp"

class PlayerController {
public:
    PlayerController(sf::Sprite sprite, const std::string& tilesetPath, int tileWidth, int tileHeight);

    // Call this every frame to update player logic
    void update(float deltaTime);

    // Draw the player
    void draw(sf::RenderWindow& window);

    // Access player position if needed
    sf::Vector2f getPosition() const;

private:
    TileManager m_tileManager; // handles animation frames for player
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    std::string m_tilesetPath;

    float m_speed = 50.f; // pixels per second
};
