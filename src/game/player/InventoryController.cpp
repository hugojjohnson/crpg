#include "game/player/InventoryController.hpp"
#include "common/input/InputManager.hpp"
#include <SFML/Graphics.hpp>
#include <stdexcept>

struct textureStruct {
  sf::Texture inventory;
  sf::Texture inventorySelector;
};

namespace {
constexpr const char *inventoryTexturePath =
    "assets/sprites/player/inventorySlot.png";
constexpr const char *inventorySelectorTexturePath =
    "assets/sprites/player/inventorySelect.png";

textureStruct &getTextures() {
  static textureStruct textures;
  //   static sf::Texture inventoryTexture;
  //   static sf::Texture inventorySelectorTexture;
  static bool loaded = false;
  if (!loaded) {
    if (!textures.inventory.loadFromFile(inventoryTexturePath)) {
      throw std::runtime_error(
          "InventoryController: failed to load inventory texture.");
    }
    if (!textures.inventorySelector.loadFromFile(
            inventorySelectorTexturePath)) {
      throw std::runtime_error(
          "InventoryController: failed to load inventory selector texture.");
    }
    loaded = true;
  }
  return textures;
}
} // namespace

InventoryController::InventoryController()
    : m_selectedIndex(1), m_inventorySprite(getTextures().inventory),
      m_inventorySelectSprite(getTextures().inventorySelector) {}

void InventoryController::draw(sf::RenderWindow &window) {
  const textureStruct textures = getTextures();

  constexpr float inventoryWidthPx = 40.f;
  constexpr float inventorySpacingPx = 0.f;
  constexpr float inventoryMarginBottomPx = 4.f;

  const sf::Vector2u inventoryTexSize = textures.inventory.getSize();
  if (inventoryTexSize.x == 0 || inventoryTexSize.y == 0) {
    return;
  }

  sf::Sprite inventorySprite = m_inventorySprite;
  const float scale = inventoryWidthPx / static_cast<float>(inventoryTexSize.x);
  inventorySprite.setScale({scale, scale});
  m_inventorySelectSprite.setScale({scale, scale});

  const sf::IntRect fullRect({0, 0}, {static_cast<int>(inventoryTexSize.x),
                                      static_cast<int>(inventoryTexSize.y)});
  const sf::IntRect halfRect({0, 0}, {static_cast<int>(inventoryTexSize.x / 2),
                                      static_cast<int>(inventoryTexSize.y)});

  int inventorySlots = 10;

  float totalInventoryWidth =
      (inventoryWidthPx + inventorySpacingPx) * (inventorySlots - 1);
  float x =
      static_cast<float>(window.getSize().x) / 2 - totalInventoryWidth / 2;
  const float y =
      window.getSize().y - inventoryWidthPx - inventoryMarginBottomPx;

  for (int i = 0; i < inventorySlots; ++i) {
    inventorySprite.setTextureRect(fullRect);
    inventorySprite.setPosition({x, y});
    window.draw(inventorySprite);
    if ((i + 1) == m_selectedIndex) {
        m_inventorySelectSprite.setPosition({x, y});
        window.draw(m_inventorySelectSprite);
    }
    x += (inventoryWidthPx + inventorySpacingPx);
  }
}

void InventoryController::update() {
    if (InputManager::instance().getKeyboardManager().isPressed(sf::Keyboard::Key::Num1)) {
        m_selectedIndex = 1;
    }
    if (InputManager::instance().getKeyboardManager().isPressed(sf::Keyboard::Key::Num2)) {
        m_selectedIndex = 2;
    }
    if (InputManager::instance().getKeyboardManager().isPressed(sf::Keyboard::Key::Num3)) {
        m_selectedIndex = 3;
    }
    if (InputManager::instance().getKeyboardManager().isPressed(sf::Keyboard::Key::Num4)) {
        m_selectedIndex = 4;
    }
    if (InputManager::instance().getKeyboardManager().isPressed(sf::Keyboard::Key::Num5)) {
        m_selectedIndex = 5;
    }
    if (InputManager::instance().getKeyboardManager().isPressed(sf::Keyboard::Key::Num6)) {
        m_selectedIndex = 6;
    }
    if (InputManager::instance().getKeyboardManager().isPressed(sf::Keyboard::Key::Num7)) {
        m_selectedIndex = 7;
    }
    if (InputManager::instance().getKeyboardManager().isPressed(sf::Keyboard::Key::Num8)) {
        m_selectedIndex = 8;
    }
    if (InputManager::instance().getKeyboardManager().isPressed(sf::Keyboard::Key::Num9)) {
        m_selectedIndex = 9;
    }
    if (InputManager::instance().getKeyboardManager().isPressed(sf::Keyboard::Key::Num0)) {
        m_selectedIndex = 10;
    }
}