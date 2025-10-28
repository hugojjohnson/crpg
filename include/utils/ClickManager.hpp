#pragma once
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>

struct ClickManager {
public:
  std::vector<std::function<void(const sf::Vector2f &)>> handlers;

  void add(auto &&clickable) {
    handlers.push_back([c = std::forward<decltype(clickable)>(clickable)](const sf::Vector2f &pos) {
    //   std::cout << "inside the function\n";
      if (c.contains(pos)) {
        // std::cout << "about to process callback!\n";
        c.cb();
      }
    });
  }

  void processClick(const sf::Vector2f &pos) {
    // std::cout << "ClickManager processing click!\n";
    for (auto &h : handlers) {
      h(pos);
    }
  }
};