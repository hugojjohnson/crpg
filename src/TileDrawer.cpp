#include "../include/TileDrawer.hpp"
#include <iostream>

TileDrawer::TileDrawer(int tileWidth, int tileHeight, int gridWidth, int gridHeight, std::string basePath)
    : m_tileManager(TileManager{tileWidth, tileHeight, basePath}), m_tileWidth(tileWidth), m_tileHeight(tileHeight), m_gridWidth(gridWidth), m_gridHeight(gridHeight), m_basePath(basePath) {}

std::string TileDrawer::key(int x, int y) { return std::to_string(x) + "," + std::to_string(y); }

void TileDrawer::addTile(int x, int y, const std::string &tilesetPath, int index) {
  if (x < 0 || y < 0 || x >= m_gridWidth || y >= m_gridHeight) {
    std::cerr << "TileDrawer: coordinates out of bounds (" << x << ", " << y << ")\n";
    return;
  }

  sf::Sprite sprite = m_tileManager.getTile(tilesetPath, index);
  sprite.setPosition({static_cast<float>(x * m_tileWidth), static_cast<float>(y * m_tileHeight)});

  m_tileMap.emplace(key(x, y), std::move(sprite));
}

bool TileDrawer::hasTile(int x, int y) const { return m_tileMap.contains(key(x, y)); }

void TileDrawer::draw(sf::RenderWindow &window) const {
  for (const auto &pair : m_tileMap) {
    window.draw(pair.second);
  }
}
