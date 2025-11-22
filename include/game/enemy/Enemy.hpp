#pragma once
#include "game/AnimationManager.hpp"
#include <SFML/Graphics.hpp>

class Enemy {
public:
  explicit Enemy(sf::Texture blankTexture, int health, sf::Vector2f pos);
  void draw(sf::RenderWindow &window);
  void update(float deltaTime);

private:
  int m_health;
  sf::Vector2f m_pos;

  sf::Sprite m_sprite;
  sf::Texture m_texture;
  // std::string m_tilesetPath = "assets/sprites/enemies/skeleton.png";
  AnimationManager m_animationManager;
  TileManager m_tileManager;
};