#pragma once

#include <SFML/Graphics.hpp>

class CameraSystem {
public:
  CameraSystem(const sf::RenderWindow &window, sf::Vector2f worldSize,
               float zoomFactor);

  void updateFocus(const sf::Vector2f &target);
  void applyWorldView(sf::RenderWindow &window) const;
  void applyUIView(sf::RenderWindow &window) const;

  const sf::View &getWorldView() const { return m_worldView; }
  const sf::View &getUIView() const { return m_uiView; }

private:
  sf::View m_worldView;
  sf::View m_uiView;
  sf::Vector2f m_worldSize;
};
