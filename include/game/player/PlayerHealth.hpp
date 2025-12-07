#include <SFML/Graphics.hpp>

class PlayerHealth {
public:
  PlayerHealth(int hp);
  void takeDamage(int damage);
  void heal(int hp);
  bool isDead();
  void draw(sf::RenderWindow &window);

private:
  int m_hp;
  int m_maxHp;
  sf::Sprite m_sprite;
};
