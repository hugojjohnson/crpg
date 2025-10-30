#include "../../include/common/BackgroundManager.hpp"
#include <SFML/Graphics.hpp>

int main5() {
  sf::RenderWindow window(sf::VideoMode({400, 400}), "BackgroundManager Test");

  BackgroundManager BackgroundManager(16, 16, 10, 10); // 10x10 grid of 16px tiles

  // Place some tiles at (tile) coordinates
  BackgroundManager.addTile(0, 0, "tiles/path_tile.png", 0);
  BackgroundManager.addTile(1, 0, "tiles/path_tile.png", 1);
  BackgroundManager.addTile(2, 0, "tiles/path_tile.png", 2);
  BackgroundManager.addTile(3, 1, "tiles/path_tile.png", 4);

  while (window.isOpen()) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    window.clear(sf::Color::Black);
    BackgroundManager.draw(window);
    window.display();
  }
  return 0;
}
