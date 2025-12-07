#include "common/BackgroundManager.hpp"
#include "common/input/InputManager.hpp"
#include "common/TileSerialiser.hpp"
#include "game/player/PlayerController.hpp"
#include "game/CameraSystem.hpp"
#include <SFML/Graphics.hpp>
#include "game/enemy/EnemyManager.hpp"

int main() {

  // Window
  sf::RenderWindow window(sf::VideoMode({16 * 40, 16 * 40}), "BackgroundManager Test");
  window.setFramerateLimit(60);

  // BackgroundManager: 16x16 tiles, 10x10 grid
  BackgroundManager BackgroundManager(16, 16, 40, 40);
  TileSerialiser tileSerialiser;

  PlayerController player(32, 32);
  EnemyManager EnemyManager{};
  EnemyManager.populateEnemies();
  CameraSystem camera(window, BackgroundManager.getWorldSize(), 0.5f);

  // Wire up callbacks
  player.m_onSwing = [&](const sf::FloatRect hb) {
    EnemyManager.onSwing(hb);
    std::cout << "Hell yeah!\n";
  };
  EnemyManager.m_damagePlayer = [&player](int damage) {
    player.health.takeDamage(damage);
  };


  // Begin building world
  sf::Clock clock;
  tileSerialiser.load("out.json", BackgroundManager);
  while (window.isOpen()) { 
    camera.applyWorldView(window);
    // Updates
    float dt = clock.restart().asSeconds();
    InputManager::instance().update(window, dt);
    EnemyManager.update(dt, player.getPosition());
    player.update(dt);
    camera.updateFocus(player.getCenter());
    camera.applyWorldView(window);

    // Draw
    window.clear(sf::Color::Black);
    BackgroundManager.draw(window);
    EnemyManager.draw(window);
    player.draw(window);
    camera.applyUIView(window);
    player.health.draw(window); // Needs to be drawn after applying the UI view
    player.inventory.draw(window);
    window.display();
  }
}
