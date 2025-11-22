#include "../../../include/game/enemy/Enemy.hpp"
#include <iostream>

Enemy::Enemy(sf::Texture blankTexture, int health, sf::Vector2f pos)
    : m_sprite(sf::Sprite{blankTexture}), m_tileManager(TileManager{16, 16}),
      m_animationManager(m_tileManager) {
  const auto tilesetPath = "assets/sprites/enemies/skeleton.png";
  if (!m_texture.loadFromFile(tilesetPath)) {
    std::cerr << "Failed to load player tileset: " << tilesetPath << "\n";
  }
  m_sprite.setTexture(m_texture);
  m_sprite.setPosition(pos); // starting in middle of screen

  m_animationManager.addAnimation(
      "idle", Animation{"enemies/skeleton.png", {0, 1}, 6.f, false});
  m_animationManager.play("idle");

  // Set up on sword click
  sf::Color white(255, 255, 255);
  sf::RectangleShape rect;
  // std::function<void()> cb = [this]() {
  //   this->m_currentState = {CurrentState::Slash, 4, 4};
  // };
  rect.setPosition({0, 0});
  rect.setSize({640, 640});
  rect.setFillColor(white);
  // InputManager::instance().getClickManager().add(Clickable(rect, cb),
  //  ClickLayer::Background);
}

void Enemy::draw(sf::RenderWindow &window) { window.draw(m_sprite); }

void Enemy::update(float deltaTime) {
  m_animationManager.update(deltaTime);
  m_sprite.setTextureRect(m_animationManager.getCurrentTexture());
}