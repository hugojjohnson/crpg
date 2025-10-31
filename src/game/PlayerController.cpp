#include "../../include/game/PlayerController.hpp"
#include "../../include/common/TileManager.hpp"
#include <iostream>

// // AnimationManager
//   TileManager tileManager(32, 32);
//   AnimationManager animManager(tileManager);

//   animManager.play("idle");

PlayerController::PlayerController(sf::Texture blankTexture, int tileWidth, int tileHeight)
    : m_sprite(sf::Sprite{blankTexture}), m_tileManager(TileManager{tileWidth, tileHeight}), m_animationPlayer(m_tileManager) {
  if (!m_texture.loadFromFile(m_tilesetPath)) {
    std::cerr << "Failed to load player tileset: " << m_tilesetPath << "\n";
  }
  m_sprite.setTexture(m_texture);
  // m_sprite.setTextureRect(m_tileManager.getTile(m_tilesetPath, 0)); // start with first tile
  m_sprite.setPosition({400.f, 300.f}); // starting in middle of screen

  m_animationPlayer.addAnimation("idle", Animation{"player/player.png", {0, 1, 2, 3, 4, 5}, 6.f});
  m_animationPlayer.addAnimation("walkLeft", Animation{"player/player.png", {6, 7, 8, 9, 10, 11}, 6.f});
  m_animationPlayer.addAnimation("walkUp", Animation{"player/player.png", {12, 13, 14, 15, 16, 17}, 6.f});
  m_animationPlayer.addAnimation("walkDown", Animation{"player/player.png", {18, 19, 20, 21, 22, 26}, 6.f});
  m_animationPlayer.play("idle");
}

void PlayerController::update(float deltaTime) {
  sf::Vector2f movement(0.f, 0.f);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    movement.y -= m_speed * deltaTime;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    movement.y += m_speed * deltaTime;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    movement.x -= m_speed * deltaTime;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    movement.x += m_speed * deltaTime;

  m_sprite.move(movement);

  //   // Optional: update animation frame based on movement
  //   if (movement.x != 0.f || movement.y != 0.f) {
  //     // For simplicity, cycle through the first 4 tiles horizontally
  //     static int frame = 0;
  //     frame = (frame + 1) % 4;
  //     m_sprite.setTextureRect(m_tileManager.getTile("player/player.png", frame).getTextureRect());
  //   }
  m_animationPlayer.update(deltaTime);
  m_sprite.setTextureRect(m_animationPlayer.getCurrentSprite().getTextureRect());
}

void PlayerController::draw(sf::RenderWindow &window) { window.draw(m_sprite); }

sf::Vector2f PlayerController::getPosition() const { return m_sprite.getPosition(); }
