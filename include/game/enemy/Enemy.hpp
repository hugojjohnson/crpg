#pragma once
#include "game/AnimationManager.hpp"
#include <SFML/Graphics.hpp>

class Enemy {
public:
  sf::Sprite m_sprite;
  explicit Enemy(int health, float movementSpeed, sf::Vector2f pos);
  void draw(sf::RenderWindow &window);
  void update(float deltaTime, sf::Vector2f playerPos);
  void moveTowardsPlayer(float deltaTime, sf::Vector2f playerPos);

private:
  int m_health;
  float m_movementSpeed;
  sf::Vector2f m_pos;

  AnimationManager m_animationManager;
  sf::Texture m_texture;
};