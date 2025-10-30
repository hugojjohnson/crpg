#include "../include/TileDrawer.hpp"
#include <SFML/Graphics.hpp>

int main5() {
  sf::RenderWindow window(sf::VideoMode({400, 400}), "TileDrawer Test");

  TileDrawer tileDrawer(16, 16, 10, 10, "assets/sprites/"); // 10x10 grid of 16px tiles

  // Place some tiles at (tile) coordinates
  tileDrawer.addTile(0, 0, "tiles/path_tile.png", 0);
  tileDrawer.addTile(1, 0, "tiles/path_tile.png", 1);
  tileDrawer.addTile(2, 0, "tiles/path_tile.png", 2);
  tileDrawer.addTile(3, 1, "tiles/path_tile.png", 4);

  while (window.isOpen()) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    window.clear(sf::Color::Black);
    tileDrawer.draw(window);
    window.display();
  }
  return 0;
}
