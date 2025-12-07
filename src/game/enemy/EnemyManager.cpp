#include "game/enemy/EnemyManager.hpp"
#include "game/enemy/Enemy.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

void EnemyManager::swordStrike(sf::Vector2f pos) {
  std::cout << "Sword stroke from EnemyManager!";
}

void EnemyManager::addEnemy(sf::Vector2f pos) {
  m_enemies.emplace_back(std::make_unique<Enemy>(100, 30.f, pos, 30));
}

void EnemyManager::populateEnemies() {
  addEnemy({10, 10});
  addEnemy({100, 100});
  addEnemy({200, 200});
}

void EnemyManager::draw(sf::RenderWindow &window) {
  for (auto &enemy : m_enemies) {
    // std::cout << "drawing";
    enemy->draw(window);
  }
}

void EnemyManager::update(float deltaTime, sf::Vector2f playerPos) {
  for (auto &enemy : m_enemies) {
    enemy->update(deltaTime, playerPos);
  }
  for (auto &enemy : m_enemies) {
    sf::Vector2f difference = enemy->m_sprite.getPosition() - playerPos;
    if (difference.length() < 10 && this->m_damagePlayer && enemy->hitCooldownFinished()) {
      this->m_damagePlayer(1);
      enemy->hitPlayer();
    }
  }
}

void EnemyManager::onSwing(const sf::FloatRect &hb) {
  std::cout << "Sword swung at " << hb.position.x << ", " << hb.position.y
            << "!\n";
  m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(),
                                 [hb](const std::unique_ptr<Enemy> &e) {
                                   sf::FloatRect enemyBounds =
                                       e->m_sprite.getGlobalBounds();
                                   return hb.findIntersection(enemyBounds);
                                 }),
                  m_enemies.end());
}
