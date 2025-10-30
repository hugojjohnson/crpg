#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main3() {
  constexpr int imageWidth = 48;
  constexpr int imageHeight = 96;
  constexpr int cols = 3;
  constexpr int rows = 6;
  constexpr int tileWidth = imageWidth / cols;
  constexpr int tileHeight = imageHeight / rows;

  sf::RenderWindow window(sf::VideoMode({300, 300}), "Image Split Demo");

  sf::Texture texture;
  if (!texture.loadFromFile("assets/sprites/tiles/path_tile.png")) {
    std::cerr << "Failed to load image!\n";
    return 1;
  }

  // Store sprites for each sub-rectangle
  std::vector<sf::Sprite> sprites;
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      sf::Sprite sprite(texture);
      sprite.setTextureRect(sf::IntRect({col * tileWidth, row * tileHeight}, {tileWidth, tileHeight}));
      // Place each tile spaced out so you can see them
      sprite.setPosition({static_cast<float>(col * (tileWidth + 4)), // +4 for padding
                          static_cast<float>(row * (tileHeight + 4))});
      sprites.push_back(sprite);
    }
  }

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    window.clear(sf::Color::Black);

    for (const auto &sprite : sprites)
      window.draw(sprite);

    window.display();
  }

  return 0;
}
