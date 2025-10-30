#pragma once
#include "TileManager.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class BackgroundManager {
public:
  struct TileInfo {
    sf::Sprite sprite;
    std::string path;
    int index;
    
    explicit TileInfo(sf::Sprite s, std::string p, int i): sprite(s), path(p), index(i) {}
  };

  BackgroundManager(int tileWidth, int tileHeight, int gridWidth, int gridHeight);

  // 2D map of grid coords -> sprite
  std::unordered_map<std::string, TileInfo> m_tileMap;
  TileManager m_tileManager;

  // Place a tile at grid position (x, y)
  void addTile(int x, int y, const std::string &tilesetPath, int index);

  // Draw all tiles
  void draw(sf::RenderWindow &window) const;

  // Optional: get info about what’s placed
  bool hasTile(int x, int y) const;

private:
  int m_tileWidth;
  int m_tileHeight;
  int m_gridWidth;
  int m_gridHeight;

  // Helper: encode grid coords as string key
  static std::string key(int x, int y);
};