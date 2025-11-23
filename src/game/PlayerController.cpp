#include "../../include/game/PlayerController.hpp"
#include "common/input/Clickable.hpp"
#include "common/input/InputManager.hpp"
#include <functional>

PlayerController::PlayerController(int tileWidth, int tileHeight)
    : m_animationPlayer(tileWidth, tileHeight), m_sprite(m_texture) {

  // Load player texture once
  std::string tilesetPath = "assets/sprites/player/player.png";
  if (!m_texture.loadFromFile(tilesetPath)) {
    throw std::runtime_error("Failed to load player tileset: " + tilesetPath);
  }

  // Create sprite with loaded texture
  m_sprite = sf::Sprite(m_texture);
  m_sprite.setPosition({400.f, 300.f});

  // Register all animations
  m_animationPlayer.addAnimation(
      "idleLeft",
      Animation{"player/player.png", {6, 7, 8, 9, 10, 11}, 6.f, true});
  m_animationPlayer.addAnimation(
      "idleRight",
      Animation{"player/player.png", {6, 7, 8, 9, 10, 11}, 6.f, false});
  m_animationPlayer.addAnimation(
      "idleUp",
      Animation{"player/player.png", {12, 13, 14, 15, 16, 17}, 6.f, false});
  m_animationPlayer.addAnimation(
      "idleDown",
      Animation{"player/player.png", {0, 1, 2, 3, 4, 5}, 6.f, false});

  // Walk
  m_animationPlayer.addAnimation(
      "walkRight",
      Animation{"player/player.png", {24, 25, 26, 27, 28, 29}, 6.f, false});
  m_animationPlayer.addAnimation(
      "walkLeft",
      Animation{"player/player.png", {24, 25, 26, 27, 28, 29}, 6.f, true});
  m_animationPlayer.addAnimation(
      "walkUp",
      Animation{"player/player.png", {30, 31, 32, 33, 34, 35}, 6.f, false});
  m_animationPlayer.addAnimation(
      "walkDown",
      Animation{"player/player.png", {18, 19, 20, 21, 22, 23}, 6.f, false});

  // Diagonals
  m_animationPlayer.addAnimation(
      "walkSW",
      Animation{"player/player.png", {24, 25, 26, 27, 28, 29}, 6.f, true});
  m_animationPlayer.addAnimation(
      "walkSE",
      Animation{"player/player.png", {24, 25, 26, 27, 28, 29}, 6.f, false});
  m_animationPlayer.addAnimation(
      "walkNW",
      Animation{"player/player.png", {30, 31, 32, 33, 34, 35}, 6.f, false});
  m_animationPlayer.addAnimation(
      "walkNE",
      Animation{"player/player.png", {30, 31, 32, 33, 34, 35}, 6.f, true});

  // Slash
  m_animationPlayer.addAnimation(
      "slashLeft", Animation{"player/player.png", {42, 43, 44, 45}, 6.f, true});
  m_animationPlayer.addAnimation(
      "slashRight",
      Animation{"player/player.png", {42, 43, 44, 45}, 6.f, false});
  m_animationPlayer.addAnimation(
      "slashUp", Animation{"player/player.png", {48, 49, 50, 51}, 6.f, false});
  m_animationPlayer.addAnimation(
      "slashDown",
      Animation{"player/player.png", {36, 37, 38, 39}, 6.f, false});

  m_animationPlayer.play("idleDown");

  // Set up on sword click
  sf::Color white(255, 255, 255);
  sf::RectangleShape rect;
  std::function<void()> cb = [this]() {
    sf::FloatRect hitbox = {m_sprite.getPosition(), {16, 16}};
    switch (m_lastDirection) {
    case Up:
      hitbox.position.y -= 8;
      break;
    case Down:
      hitbox.position.y += 8;
      break;
    case Left:
      hitbox.position.x -= 8;
      break;
    case Right:
      hitbox.position.x += 8;
      break;
    }
    if (this->m_onSwing) {
      this->m_onSwing(hitbox);
    }
    this->m_currentState = {CurrentState::Slash, 4, 4};
  };
  rect.setPosition({0, 0});
  rect.setSize({640, 640});
  rect.setFillColor(white);
  InputManager::instance().getClickManager().add(Clickable(rect, cb),
                                                 ClickLayer::Background);
}

void PlayerController::update(float deltaTime) {
  switch (m_currentState.type) {
  case CurrentState::Idle:
    updateWalk(deltaTime);
    break;
  case CurrentState::Slash:
    updateSlash(deltaTime);
    break;
  };
  m_animationPlayer.update(deltaTime);
  m_sprite.setTextureRect(m_animationPlayer.getCurrentTexture());
}

void PlayerController::updateWalk(float deltaTime) {
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
}

void PlayerController::updateSlash(float deltaTime) {
  if (m_animationPlayer.lastFrame()) {
    m_currentState = {CurrentState::Idle, 0, 0};
  }

  switch (m_lastDirection) {
  case Direction::Up:
    m_animationPlayer.play("slashUp");
    /* code */
    break;
  case Direction::Down:
    m_animationPlayer.play("slashDown");
    /* code */
    break;
  case Direction::Left:
    m_animationPlayer.play("slashLeft");
    /* code */
    break;
  case Direction::Right:
    m_animationPlayer.play("slashRight");
    /* code */
    break;
  }
}

void PlayerController::draw(sf::RenderWindow &window) { window.draw(m_sprite); }

sf::Vector2f PlayerController::getPosition() const {
  return m_sprite.getPosition();
}
