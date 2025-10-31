#include "../../include/game/AnimationManager.hpp"
#include <stdexcept>
#include <iostream>

AnimationManager::AnimationManager(TileManager &tileManager) : m_tileManager(tileManager) {}

void AnimationManager::addAnimation(const std::string &name, const Animation &animation) { m_animations[name] = animation; }

void AnimationManager::play(const std::string &name) {
  if (m_current != name) {
    if (m_animations.find(name) == m_animations.end()) {
      throw std::runtime_error("Animation not found: " + name);
    }
    m_current = name;
    m_currentFrame = 0;
    m_timer = 0.f;
  }
}

void AnimationManager::update(float deltaTime) {
  if (m_current.empty()) {
    std::cout << "Current frame is empty.\n";
    return;
  }

  auto &anim = m_animations[m_current];
  m_timer += deltaTime;

  const float frameDuration = 1.f / anim.fps;
  if (m_timer >= frameDuration) {
    m_timer -= frameDuration;
    m_currentFrame = (m_currentFrame + 1) % static_cast<int>(anim.frames.size());
  }
}

sf::IntRect AnimationManager::getCurrentTexture() const {
  if (m_current.empty()) {
    std::cout << "m_current is empty.\n";
    sf::Texture blankTexture;
    sf::Sprite tempSprite(blankTexture);
    return tempSprite.getTextureRect();
  }

  const auto &anim = m_animations.at(m_current);
  int tileIndex = anim.frames[m_currentFrame];
  sf::IntRect returnTexture = m_tileManager.getTile(anim.tilesetPath, tileIndex).getTextureRect();
  if (anim.flipHorizontally) {
    returnTexture.position.x += returnTexture.size.x;
    returnTexture.size.x = -returnTexture.size.x;  // negative width mirrors it
  }
  return returnTexture;
}