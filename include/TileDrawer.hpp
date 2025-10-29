#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "TileManager.hpp"

class TileDrawer {
public:
    TileDrawer(int tileWidth, int tileHeight, int gridWidth, int gridHeight, std::string basePath);

    // Place a tile at grid position (x, y)
    void addTile(int x, int y, const std::string &tilesetPath, int index);

    // Draw all tiles
    void draw(sf::RenderWindow &window) const;

    // Optional: get info about what’s placed
    bool hasTile(int x, int y) const;

private:
    TileManager m_tileManager;
    int m_tileWidth;
    int m_tileHeight;
    int m_gridWidth;
    int m_gridHeight;
    std::string m_basePath;

    // 2D map of grid coords -> sprite
    std::unordered_map<std::string, sf::Sprite> m_tileMap;

    // Helper: encode grid coords as string key
    static std::string key(int x, int y);
};