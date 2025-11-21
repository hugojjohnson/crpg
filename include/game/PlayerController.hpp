#pragma once
#include "../common/TileManager.hpp"
#include "AnimationManager.hpp"
#include <SFML/Graphics.hpp>

class PlayerController {
public:
  PlayerController(sf::Texture blankTexture, int tileWidth, int tileHeight);
  sf::Sprite m_sprite;

  // Call this every frame to update player logic
  void update(float deltaTime);

  // Draw the player
  void draw(sf::RenderWindow &window);

  // Access player position if needed
  sf::Vector2f getPosition() const;

private:
  enum Direction { Up, Down, Left, Right };
  struct CurrentState {
    enum { Idle, Slash } type;
    int frameDuration;
    int framesLeft;
  };
  CurrentState m_currentState = { CurrentState::Idle, 0, 0 };
  TileManager m_tileManager; // handles animation frames for player
  AnimationManager m_animationPlayer;
  sf::Texture m_texture;
  std::string m_tilesetPath = "assets/sprites/player/player.png";
  Direction m_lastDirection = Direction::Down;

  //   Update functions
  void updateWalk(float deltaTime);
  void updateSlash(float deltaTime);

  float m_speed = 50.f; // pixels per second
};
