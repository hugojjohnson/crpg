#include "../../include/common/KeyboardManager.hpp"
#include "../../include/common/BackgroundManager.hpp"
#include "../../include/common/TileSerialiser.hpp"
#include "../../include/game/PlayerController.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {

  // Window
  sf::RenderWindow window(sf::VideoMode({16 * 40, 16 * 40}), "BackgroundManager Test");
  window.setFramerateLimit(60);

  // BackgroundManager: 16x16 tiles, 10x10 grid
  BackgroundManager BackgroundManager(16, 16, 40, 40);
  TileSerialiser tileSerialiser;
  KeyboardManager keyboardManager;

  sf::Texture blankTexture;
  sf::Sprite playerTempSprite(blankTexture);
  PlayerController player(playerTempSprite, "assets/sprites/player/player.png", 32, 32);
  sf::Clock clock;

  tileSerialiser.load("out.json", BackgroundManager);

  while (window.isOpen()) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        tileSerialiser.save("out.json", BackgroundManager.m_tileMap);
        window.close();
      }
    }

    // Updtates
    keyboardManager.update();
    float dt = clock.restart().asSeconds();
    player.update(dt);

    // Draw
    window.clear(sf::Color::Black);
    BackgroundManager.draw(window);
    player.draw(window);
    window.display();
  }
}