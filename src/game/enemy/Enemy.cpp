#include "../../../include/game/enemy/Enemy.hpp"

Enemy::Enemy(int health, sf::Vector2f pos)
    : m_sprite(sf::Sprite{m_texture}), m_animationManager(32, 32) {

  std::string tilesetPath = "assets/sprites/enemies/skeleton.png";
  if (!m_texture.loadFromFile(tilesetPath)) {
    throw std::runtime_error("Failed to load enemy tileset: " + tilesetPath);
  }

  // Create sprite with loaded texture
  m_sprite = sf::Sprite(m_texture);
  m_sprite.setPosition({300.f, 300.f}); // starting in middle of screen

  m_animationManager.addAnimation(
      "idle2", Animation{"enemies/skeleton.png", {0, 1, 2, 3, 4, 5}, 6.f, false});
  m_animationManager.play("idle2");
}

void Enemy::draw(sf::RenderWindow &window) { window.draw(m_sprite); }

void Enemy::update(float deltaTime) {
  m_animationManager.update(deltaTime);
  m_sprite.setTextureRect(m_animationManager.getCurrentTexture());
}