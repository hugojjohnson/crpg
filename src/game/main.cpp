#include "../include/TileDrawer.hpp"
#include "../include/TileSerialiser.hpp"
#include "../include/KeyboardManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {

  // Window
  sf::RenderWindow window(sf::VideoMode({16*40, 16*40}), "TileDrawer Test");

  // TileDrawer: 16x16 tiles, 10x10 grid
  TileDrawer tileDrawer(16, 16, 40, 40, "assets/sprites/");
  TileSerialiser tileSerialiser;
  KeyboardManager keyboardManager;

  tileSerialiser.load("out.json", tileDrawer);

  int currentIndex = 0; // current tile index for placing

  while (window.isOpen()) {

    while (const std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        tileSerialiser.save("out.json", tileDrawer.m_tileMap);
        window.close();
      }

      if (event->is<sf::Event::MouseButtonPressed>()) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        int tileX = mousePos.x / 16;
        int tileY = mousePos.y / 16;

        tileDrawer.addTile(tileX, tileY, "tiles/path_tile.png", currentIndex);
      }

      // // Key press → increment index
      // if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
      //   if (keyPressed->code == sf::Keyboard::Key::Tab) {
      //     currentIndex++;
      //     currentIndex %= tileDrawer.m_tileManager.getNumTiles("tiles/path_tile.png");
      //     std::cout << "Current tile index: " << currentIndex << "\n";
      //   }
    }

    keyboardManager.update();

    if (keyboardManager.isHeld(sf::Keyboard::Key::Space)) {
      std::cout << "Space is held! ";
    }

    if (keyboardManager.isReleased(sf::Keyboard::Key::Space)) {
      std::cout << "\nSpace is released!\n";
    }

    // Draw everything
    window.clear(sf::Color::Black);
    tileDrawer.draw(window);
    window.display();
  }
}