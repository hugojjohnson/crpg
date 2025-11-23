#pragma once
#include "game/AnimationManager.hpp"
#include <SFML/Graphics.hpp>

class Enemy {
public:
  sf::Sprite m_sprite;
  explicit Enemy(int health, sf::Vector2f pos);
  void draw(sf::RenderWindow &window);
  void update(float deltaTime);

private:
  int m_health;
  sf::Vector2f m_pos;

  AnimationManager m_animationManager;
  sf::Texture m_texture;
};