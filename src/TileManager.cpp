#include "../include/TileManager.hpp"
#include <iostream>

TileManager::TileManager(int tileWidth, int tileHeight, std::string basePath) : m_tileWidth(tileWidth), m_tileHeight(tileHeight), m_basePath(basePath) {}

bool TileManager::loadIfNeeded(const std::string &path) {
  if (m_textures.contains(path))
    return true;

  sf::Texture texture;
  if (!texture.loadFromFile(m_basePath + path)) {
    std::cerr << "TileManager: Failed to load texture: " << path << '\n';
    return false;
  }

  m_textures.emplace(path, std::move(texture));
  return true;
}

sf::Sprite TileManager::getTile(const std::string &path, int index) {
  if (!loadIfNeeded(path)) {
    throw std::runtime_error("Failed to load tile.");
  }

  const sf::Texture &texture = m_textures.at(path);

  int cols = texture.getSize().x / m_tileWidth;
  int x = (index % cols) * m_tileWidth;
  int y = (index / cols) * m_tileHeight;

  sf::Sprite sprite(texture);
  sprite.setTextureRect(sf::IntRect({x, y}, {m_tileWidth, m_tileHeight}));
  return sprite;
}

int TileManager::getNumTiles(const std::string &path) {
  if (!loadIfNeeded(path))
    return 0;

  const sf::Texture &texture = m_textures.at(path);
  int cols = texture.getSize().x / m_tileWidth;
  int rows = texture.getSize().y / m_tileHeight;
  return cols * rows;
}