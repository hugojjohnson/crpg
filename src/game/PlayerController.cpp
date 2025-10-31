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

  m_animationPlayer.addAnimation("idleLeft", Animation{"player/player.png", {6, 7, 8, 9, 10, 11}, 6.f, true});
  m_animationPlayer.addAnimation("idleRight", Animation{"player/player.png", {6, 7, 8, 9, 10, 11}, 6.f, false});
  m_animationPlayer.addAnimation("idleUp", Animation{"player/player.png", {12, 13, 14, 15, 16, 17}, 6.f, false});
  m_animationPlayer.addAnimation("idleDown", Animation{"player/player.png", {0, 1, 2, 3, 4, 5}, 6.f, false});

  m_animationPlayer.addAnimation("walkRight", Animation{"player/player.png", {24, 25, 26, 27, 28, 29}, 6.f, false});
  m_animationPlayer.addAnimation("walkLeft", Animation{"player/player.png", {24, 25, 26, 27, 28, 29}, 6.f, true});
  m_animationPlayer.addAnimation("walkUp", Animation{"player/player.png", {30, 31, 32, 33, 34, 35}, 6.f, false});
  m_animationPlayer.addAnimation("walkDown", Animation{"player/player.png", {18, 19, 20, 21, 22, 23}, 6.f, false});

  m_animationPlayer.addAnimation("walkSW", Animation{"player/player.png", {24, 25, 26, 27, 28, 29}, 6.f, true});
  m_animationPlayer.addAnimation("walkSE", Animation{"player/player.png", {24, 25, 26, 27, 28, 29}, 6.f, false});
  m_animationPlayer.addAnimation("walkNW", Animation{"player/player.png", {30, 31, 32, 33, 34, 35}, 6.f, false});
  m_animationPlayer.addAnimation("walkNE", Animation{"player/player.png", {30, 31, 32, 33, 34, 35}, 6.f, true});
  m_animationPlayer.play("idleDown");
}

void PlayerController::update(float deltaTime) {
  sf::Vector2f movement(0.f, 0.f);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
    movement.y -= m_speed * deltaTime;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
    movement.y += m_speed * deltaTime;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    movement.x -= m_speed * deltaTime;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
    movement.x += m_speed * deltaTime;
  }

  if (movement.x == 0 && movement.y < 0) {
    m_animationPlayer.play("walkUp");
    m_lastDirection = Direction::Up;
  } else if (movement.x == 0 && movement.y > 0) {
    m_animationPlayer.play("walkDown");
    m_lastDirection = Direction::Down;
  } else if (movement.x < 0 && movement.y == 0) {
    m_animationPlayer.play("walkLeft");
    m_lastDirection = Direction::Left;
  } else if (movement.x > 0 && movement.y == 0) {
    m_animationPlayer.play("walkRight");
    m_lastDirection = Direction::Right;
  } else if (movement.x > 0 && movement.y < 0) {
    m_animationPlayer.play("walkNE");
  } else if (movement.x < 0 && movement.y < 0) {
    m_animationPlayer.play("walkNW");
  } else if (movement.x > 0 && movement.y > 0) {
    m_animationPlayer.play("walkSE");
  } else if (movement.x < 0 && movement.y > 0) {
    m_animationPlayer.play("walkSW");
  } else {
    switch (m_lastDirection) {
    case Direction::Up:
      m_animationPlayer.play("idleUp");
      /* code */
      break;
    case Direction::Down:
      m_animationPlayer.play("idleDown");
      /* code */
      break;
    case Direction::Left:
      m_animationPlayer.play("idleLeft");
      /* code */
      break;
    case Direction::Right:
      m_animationPlayer.play("idleRight");
      /* code */
      break;
    }
  }

  if (movement.x != 0 & movement.y != 0) {
    movement.x /= 1.414;
    movement.y /= 1.414;
  }

  m_sprite.move(movement);

  //   // Optional: update animation frame based on movement
  //   if (movement.x != 0.f || movement.y != 0.f) {
  //     // For simplicity, cycle through the first 4 tiles horizontally
  //     static int frame = 0;
  //     frame = (frame + 1) % 4;
  //     m_sprite.setTextureRect(m_tileManager.getTile("player/player.png", frame).getTextureRect());
  //   }
  m_animationPlayer.update(deltaTime);
  m_sprite.setTextureRect(m_animationPlayer.getCurrentTexture());
}

void PlayerController::draw(sf::RenderWindow &window) { window.draw(m_sprite); }

sf::Vector2f PlayerController::getPosition() const { return m_sprite.getPosition(); }
