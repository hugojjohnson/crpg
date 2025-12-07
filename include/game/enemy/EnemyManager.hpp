#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <vector>
#include "game/enemy/Enemy.hpp"

class EnemyManager {
public:
  //   Functions
  void swordStrike(sf::Vector2f pos);
  void addEnemy(sf::Vector2f pos);
  void populateEnemies();
  void draw(sf::RenderWindow &window);
  void update(float deltaTime, sf::Vector2f playerPos);

  void onSwing(const sf::FloatRect &pos);
  std::function<void(int damage)> m_damagePlayer;

private:
  std::vector<int> x;
  std::vector<std::unique_ptr<Enemy>> m_enemies;
};
