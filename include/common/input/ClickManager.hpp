#pragma once
#include "Clickable.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <iostream>

enum class ClickLayer { UI, Background };

// Type-erased wrapper to hold heterogeneous Clickables
struct IClickable {
  virtual bool contains(const sf::Vector2f &pos) const = 0;
  virtual void click() = 0;
  virtual ~IClickable() = default;
};

template <typename T> struct ClickableWrapper : IClickable {
  Clickable<T> c;

  explicit ClickableWrapper(Clickable<T> clickable) : c(std::move(clickable)) {}

  bool contains(const sf::Vector2f &pos) const override { return c.contains(pos); }
  void click() override { c.cb(); }
};

class ClickManager {
public:
  std::unordered_map<ClickLayer, std::vector<std::unique_ptr<IClickable>>> itemsByLayer;

  template <typename T> void add(Clickable<T> c, ClickLayer layer = ClickLayer::Background) { itemsByLayer[layer].push_back(std::make_unique<ClickableWrapper<T>>(std::move(c))); }

  void processClick(const sf::Vector2f &pos) {
    // UI first (so menus get priority)
    for (auto layer : {ClickLayer::UI, ClickLayer::Background}) {
      auto &items = itemsByLayer[layer];
      for (auto &item : items) {
        item->click();
        if (item->contains(pos)) {
          item->click();
          return;
        }
      }
    }
    if (generalInteraction) {
        generalInteraction(pos);
    }
  }

  void clear() {
    for (auto &[_, v] : itemsByLayer) {
      v.clear();
    }
  }

  void setGeneralInteraction(std::function<void(sf::Vector2f)> func) {
    generalInteraction = func;
  }

private:
  std::function<void(sf::Vector2f)> generalInteraction;
};