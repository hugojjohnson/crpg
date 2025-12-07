#include "../../../include/game/enemy/Enemy.hpp"

Enemy::Enemy(int health, float movementSpeed, sf::Vector2f pos, int hitCooldown)
    : m_health(health), m_movementSpeed(movementSpeed),
      m_sprite(sf::Sprite{m_texture}), m_animationManager(32, 32),
      m_hitCooldown(hitCooldown),
      m_hitCooldownCounter(0) {

  std::string tilesetPath = "assets/sprites/enemies/skeleton.png";
  if (!m_texture.loadFromFile(tilesetPath)) {
    throw std::runtime_error("Failed to load enemy tileset: " + tilesetPath);
  }

  // Create sprite with loaded texture
  m_sprite = sf::Sprite(m_texture);
  m_sprite.setPosition({300.f, 300.f}); // starting in middle of screen

  // Register all animations
  m_animationManager.addAnimation(
      "idleLeft",
      Animation{"enemies/skeleton.png", {6, 7, 8, 9, 10, 11}, 7.2f, true});
  m_animationManager.addAnimation(
      "idleRight",
      Animation{"enemies/skeleton.png", {6, 7, 8, 9, 10, 11}, 7.2f, false});
  m_animationManager.addAnimation(
      "idleUp",
      Animation{"enemies/skeleton.png", {12, 13, 14, 15, 16, 17}, 7.2f, false});
  m_animationManager.addAnimation(
      "idleDown",
      Animation{"enemies/skeleton.png", {0, 1, 2, 3, 4, 5}, 7.2f, false});

  // Walk
  m_animationManager.addAnimation(
      "walkRight",
      Animation{"enemies/skeleton.png", {24, 25, 26, 27, 28, 29}, 7.2f, false});
  m_animationManager.addAnimation(
      "walkLeft",
      Animation{"enemies/skeleton.png", {24, 25, 26, 27, 28, 29}, 7.2f, true});
  m_animationManager.addAnimation(
      "walkUp",
      Animation{"enemies/skeleton.png", {30, 31, 32, 33, 34, 35}, 7.2f, false});
  m_animationManager.addAnimation(
      "walkDown",
      Animation{"enemies/skeleton.png", {18, 19, 20, 21, 22, 23}, 7.2f, false});

  // Diagonals
  m_animationManager.addAnimation(
      "walkSW",
      Animation{"enemies/skeleton.png", {24, 25, 26, 27, 28, 29}, 7.2f, true});
  m_animationManager.addAnimation(
      "walkSE",
      Animation{"enemies/skeleton.png", {24, 25, 26, 27, 28, 29}, 7.2f, false});
  m_animationManager.addAnimation(
      "walkNW",
      Animation{"enemies/skeleton.png", {30, 31, 32, 33, 34, 35}, 7.2f, false});
  m_animationManager.addAnimation(
      "walkNE",
      Animation{"enemies/skeleton.png", {30, 31, 32, 33, 34, 35}, 7.2f, true});

  // Slash
  m_animationManager.addAnimation(
      "slashLeft",
      Animation{"enemies/skeleton.png", {42, 43, 44, 45}, 7.2f, true});
  m_animationManager.addAnimation(
      "slashRight",
      Animation{"enemies/skeleton.png", {42, 43, 44, 45}, 7.2f, false});
  m_animationManager.addAnimation(
      "slashUp",
      Animation{"enemies/skeleton.png", {48, 49, 50, 51}, 7.2f, false});
  m_animationManager.addAnimation(
      "slashDown",
      Animation{"enemies/skeleton.png", {36, 37, 38, 39}, 7.2f, false});

  m_animationManager.play("idleDown");
}

void Enemy::draw(sf::RenderWindow &window) { window.draw(m_sprite); }

void Enemy::update(float deltaTime, sf::Vector2f playerPos) {
  moveTowardsPlayer(deltaTime, playerPos);

  m_animationManager.update(deltaTime);
  m_sprite.setTextureRect(m_animationManager.getCurrentTexture());

  if (m_hitCooldownCounter > 0) {
    m_hitCooldownCounter--;
  }
}

bool Enemy::hitCooldownFinished() { return m_hitCooldownCounter == 0; }
void Enemy::hitPlayer() {
  m_hitCooldownCounter = m_hitCooldown;
}

void Enemy::moveTowardsPlayer(float deltaTime, sf::Vector2f playerPos) {
  sf::Vector2f movement = playerPos - m_sprite.getPosition();
  movement = movement.normalized() * m_movementSpeed * deltaTime;

  if (movement.x == 0 && movement.y < 0) {
    m_animationManager.play("walkUp");
  } else if (movement.x == 0 && movement.y > 0) {
    m_animationManager.play("walkDown");
  } else if (movement.x < 0 && movement.y == 0) {
    m_animationManager.play("walkLeft");
  } else if (movement.x > 0 && movement.y == 0) {
    m_animationManager.play("walkRight");
  } else if (movement.x > 0 && movement.y < 0) {
    m_animationManager.play("walkNE");
  } else if (movement.x < 0 && movement.y < 0) {
    m_animationManager.play("walkNW");
  } else if (movement.x > 0 && movement.y > 0) {
    m_animationManager.play("walkSE");
  } else if (movement.x < 0 && movement.y > 0) {
    m_animationManager.play("walkSW");
  }
  m_sprite.move(movement);
}