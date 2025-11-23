#pragma once
#include "AnimationManager.hpp"
#include <SFML/Graphics.hpp>
#include <functional>

class PlayerController {

public:
  PlayerController(int tileWidth, int tileHeight);
  sf::Sprite m_sprite;

  // Call back on swing sword
  std::function<void(const sf::FloatRect &)> m_onSwing; // the callback
  // void swingSword(sf::Vector2f pos);

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
  CurrentState m_currentState = {CurrentState::Idle, 0, 0};
  AnimationManager m_animationPlayer;
  sf::Texture m_texture;
  Direction m_lastDirection = Direction::Down;

  //   Update functions
  void updateWalk(float deltaTime);
  void updateSlash(float deltaTime);

  float m_speed = 50.f; // pixels per second
};
