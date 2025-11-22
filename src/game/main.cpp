#include "common/BackgroundManager.hpp"
#include "common/input/InputManager.hpp"
#include "common/TileSerialiser.hpp"
#include "game/PlayerController.hpp"
#include <SFML/Graphics.hpp>
#include "game/enemy/EnemyController.hpp"

int main() {

  // Window
  sf::RenderWindow window(sf::VideoMode({16 * 40, 16 * 40}), "BackgroundManager Test");
  window.setFramerateLimit(60);
  sf::View view = window.getDefaultView();

  view.zoom(0.5f); // smaller factor zooms in (so things look bigger)
  window.setView(view);

  // BackgroundManager: 16x16 tiles, 10x10 grid
  BackgroundManager BackgroundManager(16, 16, 40, 40);
  TileSerialiser tileSerialiser;

  sf::Texture blankTexture;
  PlayerController player(blankTexture, 32, 32);
  EnemyController enemyController{};
  enemyController.populateEnemies();

  sf::Clock clock;

  tileSerialiser.load("out.json", BackgroundManager);

  while (window.isOpen()) { 
    // Updtates
    // keyboardManager.update();
    float dt = clock.restart().asSeconds();
    InputManager::instance().update(window, dt);
    enemyController.update(dt);
    player.update(dt);

    // Draw
    window.clear(sf::Color::Black);
    // BackgroundManager.draw(window);
    enemyController.draw(window);
    player.draw(window);
    window.display();
  }
}