#include "../../include/game/AnimationManager.hpp"
#include <iostream>
#include <stdexcept>

AnimationManager::AnimationManager(int tileWidth, int tileHeight)
    : m_tileManager{tileWidth, tileHeight} {}

void AnimationManager::addAnimation(const std::string &name,
                                    const Animation &animation) {
  m_animations[name] = animation;
}

void AnimationManager::play(const std::string &name) {
  if (m_current != name) {
    const auto it = m_animations.find(name);

    if (it == m_animations.end()) {
      throw std::runtime_error("Animation not found: " + name);
    }

    if (it->second.frames.empty()) {
      throw std::runtime_error("Animation has no frames: " + name);
    }

    m_current = name;
    m_currentFrame = 0;
    m_timer = 0.f;
  }
}

void AnimationManager::update(float deltaTime) {
  if (m_current.empty()) {
    return;
  }

  auto &anim = m_animations.at(m_current);

  if (anim.frames.empty()) {
    return;
  }

  m_timer += deltaTime;
  const float frameDuration = 1.f / anim.fps;

  while (m_timer >= frameDuration) {
    m_timer -= frameDuration;
    m_currentFrame =
        (m_currentFrame + 1) % static_cast<int>(anim.frames.size());
  }
}

sf::IntRect AnimationManager::getCurrentTexture() {
  if (m_current.empty()) {
    std::cerr << "AnimationManager: No current animation.\n";
    return sf::IntRect({0, 0}, {0, 0});
  }

  const auto &anim = m_animations.at(m_current);

  if (anim.frames.empty()) {
    throw std::runtime_error("AnimationManager: Animation has zero frames: " +
                             m_current);
  }

  int tileIndex = anim.frames[m_currentFrame];

  sf::Sprite sprite = m_tileManager.getTile(anim.tilesetPath, tileIndex);
  sf::IntRect rect = sprite.getTextureRect();

  if (anim.flipHorizontally) {
    rect.position.x += rect.size.x;
    rect.size.x = -rect.size.x;
  }

  return rect;
}

bool AnimationManager::lastFrame() const {
  if (m_current.empty()) {
    std::cerr << "m_current is empty.\n";
    return true; // default to go back to idle
  }
  const auto &anim = m_animations.at(m_current);
  return m_currentFrame == anim.frames.size() - 1;
}