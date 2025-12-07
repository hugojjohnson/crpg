#pragma once
#include "game/animation/AnimationManager.hpp"
#include <SFML/Graphics.hpp>

class Enemy {
public:
  sf::Sprite m_sprite;
  explicit Enemy(int health, float movementSpeed, sf::Vector2f pos, int hitCooldown);
  void draw(sf::RenderWindow &window);
  void update(float deltaTime, sf::Vector2f playerPos);
  void moveTowardsPlayer(float deltaTime, sf::Vector2f playerPos);
  bool hitCooldownFinished();
  void hitPlayer();

private:
  int m_hitCooldown; // Set: The cooldown in frames (e.g. 30).
  int m_hitCooldownCounter; // Temporary. Gets set to 30 and cools down.
  int m_health;
  float m_movementSpeed;
  sf::Vector2f m_pos;

  AnimationManager m_animationManager;
  sf::Texture m_texture;
};