#include "../include/Utils.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {
  // Create the main window
  sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "SFML window");
  window.setFramerateLimit(60);

  // Load a sprite to display
  const sf::Texture catTexture("assets/cat.jpg");
  sf::Sprite catSprite(catTexture);
  catSprite.setScale({0.1f, 0.1f});

  // Create a graphical text to display
  const sf::Font font("assets/arial.ttf");
  sf::Text text(font, "Hello SFML", 50);

  // Load a music to play
  sf::Music music("assets/audio.mp3");

  // Play the music
  music.play();

  // Variables
  sf::Vector2f velocity = {1.f, 1.f};

  // Start the game loop
  while (window.isOpen()) {
    // Process events
    while (const std::optional event = window.pollEvent()) {
      // Close window: exit
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    // Clear screen
    window.clear(sf::Color(0, 0, 139));

    // Draw the sprite
    // if (isOffScreen(catSprite, SCREEN_WIDTH, SCREEN_HEIGHT)) {
    //     acceleration = -acceleration;
    // }
    // Left or right wall
    sf::FloatRect b = catSprite.getGlobalBounds();
    if (b.position.x < 0 || b.position.x + b.size.x > SCREEN_WIDTH) {
      velocity.x = -velocity.x;
    }

    // Top or bottom wall
    if (b.position.y < 0 || b.position.y + b.size.y > SCREEN_HEIGHT) {
      velocity.y = -velocity.y;
    }
    catSprite.move(velocity);
    window.draw(catSprite);

    // Draw the string
    window.draw(text);

    // Update the window
    window.display();
  }
}