#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "game/enemy/Enemy.hpp"

class EnemyController {
public:
  //   Functions
  void swordStrike(sf::Vector2f pos);
  void addEnemy(sf::Vector2f pos);
  void populateEnemies();
  void draw(sf::RenderWindow &window);
  void update(float deltaTime);

private:
  std::vector<int> x;
  std::vector<std::unique_ptr<Enemy>> m_enemies;
};
