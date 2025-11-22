#include <iostream>
#include <SFML/Graphics.hpp>
#include "game/enemy/EnemyController.hpp"
#include "game/enemy/Enemy.hpp"


void EnemyController::swordStrike(sf::Vector2f pos) {
    std::cout << "Sword stroke from EnemyController!";
}

void EnemyController::addEnemy(sf::Vector2f pos) {
    sf::Texture blankTexture;
    m_enemies.push_back(Enemy{blankTexture, 100, pos});
}

void EnemyController::populateEnemies() {
    addEnemy({10, 10});
    addEnemy({100, 100});
    addEnemy({200, 200});
}

void EnemyController::draw(sf::RenderWindow &window) {
    for (auto enemy : m_enemies) {
        enemy.draw(window);
    }
}

void EnemyController::update(float deltaTime) {
    for (auto enemy : m_enemies) {
        enemy.update(deltaTime);
    }
}