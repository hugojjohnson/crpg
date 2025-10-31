#include "../../include/game/PlayerController.hpp"
#include "../../include/common/TileManager.hpp"
#include <iostream>

PlayerController::PlayerController(sf::Sprite sprite, const std::string& tilesetPath, int tileWidth, int tileHeight)
    : m_sprite(sprite), m_tileManager(TileManager{tileWidth, tileHeight}), m_tilesetPath(tilesetPath)
{
    if (!m_texture.loadFromFile(tilesetPath)) {
        std::cerr << "Failed to load player tileset: " << tilesetPath << "\n";
    }
    m_sprite.setTexture(m_texture);
    // m_sprite.setTextureRect(m_tileManager.getTile(m_tilesetPath, 0)); // start with first tile
    m_sprite.setPosition({400.f, 300.f}); // starting in middle of screen
}

void PlayerController::update(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= m_speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += m_speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= m_speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += m_speed * deltaTime;

    m_sprite.move(movement);

    // Optional: update animation frame based on movement
    if (movement.x != 0.f || movement.y != 0.f) {
        // For simplicity, cycle through the first 4 tiles horizontally
        static int frame = 0;
        frame = (frame + 1) % 4;
        m_sprite.setTextureRect(m_tileManager.getTile("player/player.png", frame).getTextureRect());
    }
}

void PlayerController::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

sf::Vector2f PlayerController::getPosition() const {
    return m_sprite.getPosition();
}
