#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "game/enemy/EnemyController.hpp"
#include "game/enemy/Enemy.hpp"


void EnemyController::swordStrike(sf::Vector2f pos) {
    std::cout << "Sword stroke from EnemyController!";
}

void EnemyController::addEnemy(sf::Vector2f pos) {
    m_enemies.emplace_back(std::make_unique<Enemy>(100, 30.f, pos));
}

void EnemyController::populateEnemies() {
    addEnemy({10, 10});
    addEnemy({100, 100});
    addEnemy({200, 200});
}

void EnemyController::draw(sf::RenderWindow &window) {
    for (auto &enemy : m_enemies) {
        // std::cout << "drawing";
        enemy->draw(window);
    }
}

void EnemyController::update(float deltaTime, sf::Vector2f playerPos) {
    for (auto &enemy : m_enemies) {
        enemy->update(deltaTime, playerPos);
    }
}

void EnemyController::onSwing(const sf::FloatRect &hb) {
    std::cout << "Sword swung at " << hb.position.x << ", " << hb.position.y << "!\n";
    m_enemies.erase(
    std::remove_if(
        m_enemies.begin(),
        m_enemies.end(),
        [hb](const std::unique_ptr<Enemy>& e) {
            sf::FloatRect enemyBounds = e->m_sprite.getGlobalBounds();
            return hb.findIntersection(enemyBounds);
        }
    ),
    m_enemies.end()
);
}
