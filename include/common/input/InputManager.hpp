#pragma once
#include "ClickManager.hpp"
#include "KeyboardManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

// Singleton InputManager
class InputManager {
public:
  // Access the singleton
  static InputManager &instance() {
    static InputManager inst;
    return inst;
  }

  // Update should be called once per frame
  void update(sf::RenderWindow &window, float dt) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      // Mouse button pressed
      if (event->is<sf::Event::MouseButtonPressed>()) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        clickManager.processClick(mousePos);
      }
    }
    // Continuous keyboard state update
    keyboardManager.update();
  }

  // Accessors
  ClickManager &getClickManager() { return clickManager; }
  KeyboardManager &getKeyboardManager() { return keyboardManager; }

private:
  // Private constructor for singleton
  InputManager() = default;

  ClickManager clickManager;
  KeyboardManager keyboardManager;

  // Delete copy/move to enforce singleton
  InputManager(const InputManager &) = delete;
  InputManager &operator=(const InputManager &) = delete;
  InputManager(InputManager &&) = delete;
  InputManager &operator=(InputManager &&) = delete;
};
