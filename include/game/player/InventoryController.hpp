#include <SFML/Graphics.hpp>

class InventoryController {
public:
  InventoryController();
  void draw(sf::RenderWindow &window);
  void update();

private:
  int m_selectedIndex;
  sf::Sprite m_inventorySprite;
  sf::Sprite m_inventorySelectSprite;
};