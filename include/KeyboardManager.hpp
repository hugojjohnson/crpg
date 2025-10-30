#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <array>

class KeyboardManager {
public:
  KeyboardManager();

  // Call once per frame to update key states
  void update();

  // Query methods
  bool isPressed(sf::Keyboard::Key key) const;
  bool isReleased(sf::Keyboard::Key key) const;
  bool isHeld(sf::Keyboard::Key key) const;

private:
  std::array<bool, sf::Keyboard::KeyCount> m_current{};
  std::array<bool, sf::Keyboard::KeyCount> m_previous{};
};