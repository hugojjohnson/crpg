#pragma once
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Clickable.hpp"

// Type-erased wrapper to hold heterogeneous Clickables
struct IClickable {
    virtual bool contains(const sf::Vector2f& pos) const = 0;
    virtual void click() = 0;
    virtual ~IClickable() = default;
};

template <typename T>
struct ClickableWrapper : IClickable {
    Clickable<T> c;

    explicit ClickableWrapper(Clickable<T> clickable) : c(std::move(clickable)) {}

    bool contains(const sf::Vector2f& pos) const override { return c.contains(pos); }
    void click() override { c.cb(); }
};

class ClickManager {
public:
    std::vector<std::unique_ptr<IClickable>> items;

    template <typename T>
    void add(Clickable<T> c) {
        items.push_back(std::make_unique<ClickableWrapper<T>>(std::move(c)));
    }

    void processClick(const sf::Vector2f& pos) {
        for (auto& item : items) {
            if (item->contains(pos))
                item->click();
        }
    }
};