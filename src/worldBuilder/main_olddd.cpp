#include <SFML/Graphics.hpp>
#include "../../include/common/TileManager.hpp"

int main4() {
    sf::RenderWindow window(sf::VideoMode({300, 300}), "Tile Manager Test");
    TileManager tileManager(16, 16);

    // Get tile index 4 (zero-based)
    sf::Sprite sprite = tileManager.getTile("tiles/path_tile.png", 4);
    sprite.setPosition({100.f, 100.f});

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

    return 0;
}
