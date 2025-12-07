#include "game/CameraSystem.hpp"
#include <algorithm>

namespace {
sf::Vector2f clampCenter(const sf::View &view, sf::Vector2f worldSize,
                         const sf::Vector2f &target) {
  sf::Vector2f center = target;
  const sf::Vector2f halfExtent{view.getSize().x / 2.f,
                                view.getSize().y / 2.f};

  if (worldSize.x <= view.getSize().x) {
    center.x = worldSize.x / 2.f;
  } else {
    center.x = std::clamp(target.x, halfExtent.x, worldSize.x - halfExtent.x);
  }

  if (worldSize.y <= view.getSize().y) {
    center.y = worldSize.y / 2.f;
  } else {
    center.y = std::clamp(target.y, halfExtent.y, worldSize.y - halfExtent.y);
  }

  return center;
}
} // namespace

CameraSystem::CameraSystem(const sf::RenderWindow &window,
                           sf::Vector2f worldSize, float zoomFactor)
    : m_worldView(window.getDefaultView()), m_uiView(window.getDefaultView()),
      m_worldSize(worldSize) {
  m_worldView.zoom(zoomFactor);
  m_worldView.setCenter(clampCenter(m_worldView, m_worldSize,
                                    m_worldView.getCenter()));
}

void CameraSystem::updateFocus(const sf::Vector2f &target) {
  m_worldView.setCenter(clampCenter(m_worldView, m_worldSize, target));
}

void CameraSystem::applyWorldView(sf::RenderWindow &window) const {
  window.setView(m_worldView);
}

void CameraSystem::applyUIView(sf::RenderWindow &window) const {
  window.setView(m_uiView);
}
