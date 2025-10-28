#pragma once
#include <functional>
#include <SFML/Graphics.hpp>

template <typename T>
concept DrawableLike = std::is_base_of_v<sf::Drawable, T>;
template <DrawableLike T> class Clickable {
public:
  T &d;
  std::function<void()> cb;
  explicit Clickable(T &drawable, std::function<void()> callback) : d(drawable), cb(callback) {}

  bool contains(const sf::Vector2f &pos) const { return d.getGlobalBounds().contains(pos); }
};