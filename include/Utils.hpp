#include <SFML/Graphics.hpp>

bool isOffScreen(const sf::Sprite& sprite, unsigned int screenWidth, unsigned int screenHeight) {
    sf::FloatRect b = sprite.getGlobalBounds();
    return b.position.x < 0 || b.position.y < 0 || 
           b.position.x + b.size.x > screenWidth || 
           b.position.y + b.size.y > screenHeight;
}
