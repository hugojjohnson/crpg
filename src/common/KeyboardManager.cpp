#include "../include/KeyboardManager.hpp"

KeyboardManager::KeyboardManager() {
    m_current.fill(false);
    m_previous.fill(false);
}

void KeyboardManager::update() {
    // Copy current to previous before updating
    m_previous = m_current;

    // Poll the actual keyboard state from SFML
    for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
        m_current[i] = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));
    }
}

bool KeyboardManager::isPressed(sf::Keyboard::Key key) const {
    auto idx = static_cast<std::size_t>(key);
    return !m_previous[idx] && m_current[idx];
}

bool KeyboardManager::isReleased(sf::Keyboard::Key key) const {
    auto idx = static_cast<std::size_t>(key);
    return m_previous[idx] && !m_current[idx];
}

bool KeyboardManager::isHeld(sf::Keyboard::Key key) const {
    auto idx = static_cast<std::size_t>(key);
    return m_previous[idx] && m_current[idx];
}