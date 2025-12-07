#include "game/player/PlayerHealth.hpp"
#include <SFML/Graphics.hpp>
#include <stdexcept>

namespace {
constexpr const char *kHeartTexturePath = "assets/sprites/ui/heart.png";

sf::Texture &getHeartTexture() {
  static sf::Texture texture;
  static bool loaded = false;
  if (!loaded) {
    if (!texture.loadFromFile(kHeartTexturePath)) {
      throw std::runtime_error("PlayerHealth: failed to load heart texture.");
    }
    loaded = true;
  }
  return texture;
}
} // namespace

PlayerHealth::PlayerHealth(int hp)
    : m_hp(hp), m_maxHp(hp), m_sprite(getHeartTexture()) {}

void PlayerHealth::takeDamage(int damage) {
  m_hp -= damage;
  if (m_hp < 0) {
    m_hp = 0;
  }
}

void PlayerHealth::heal(int hp) {
  m_hp += hp;
  if (m_hp > m_maxHp) {
    m_hp = m_maxHp;
  }
}

bool PlayerHealth::isDead() { return m_hp == 0; }

void PlayerHealth::draw(sf::RenderWindow &window) {
  if (m_hp <= 0) {
    return;
  }

  const sf::Texture texture = m_sprite.getTexture();

  constexpr float kHeartWidthPx = 10.f;
  constexpr float kHeartSpacingPx = 2.f;
  constexpr float kScreenMarginPx = 8.f;

  const sf::Vector2u texSize = texture.getSize();
  if (texSize.x == 0 || texSize.y == 0) {
    return;
  }

  sf::Sprite heartSprite = m_sprite;
  const float scale = kHeartWidthPx / static_cast<float>(texSize.x);
  heartSprite.setScale({scale, scale});

  const sf::IntRect fullRect(
      {0, 0}, {static_cast<int>(texSize.x), static_cast<int>(texSize.y)});
  const sf::IntRect halfRect(
      {0, 0}, {static_cast<int>(texSize.x / 2), static_cast<int>(texSize.y)});

  int fullHearts = m_hp / 2;
  bool hasHalfHeart = (m_hp % 2) != 0;

  float x =
      static_cast<float>(window.getSize().x) - kScreenMarginPx - kHeartWidthPx;
  const float y = kScreenMarginPx;

  for (int i = 0; i < fullHearts; ++i) {
    heartSprite.setTextureRect(fullRect);
    heartSprite.setPosition({x, y});
    window.draw(heartSprite);
    x -= (kHeartWidthPx + kHeartSpacingPx);
  }

  if (hasHalfHeart) {
    heartSprite.setTextureRect(halfRect);
    heartSprite.setPosition({x, y});
    window.draw(heartSprite);
  }
}
