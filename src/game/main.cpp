#include "../../include/common/BackgroundManager.hpp"
#include "../../include/common/input/InputManager.hpp"
#include "../../include/common/TileSerialiser.hpp"
#include "../../include/game/PlayerController.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

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

  sf::Clock clock;

  tileSerialiser.load("out.json", BackgroundManager);

  while (window.isOpen()) { 
    // Updtates
    // keyboardManager.update();
    float dt = clock.restart().asSeconds();
    InputManager::instance().update(window, dt);
    player.update(dt);

    // Draw
    window.clear(sf::Color::Black);
    BackgroundManager.draw(window);
    player.draw(window);
    window.display();
  }
}