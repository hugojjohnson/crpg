#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TileManager {
public:
    explicit TileManager(int tileWidth, int tileHeight, std::string basePath);

    // load a tileset from the path specified
    bool loadTileSet(const std::string &path);

    // load a tileset at a given index from a specific tileset
    sf::Sprite getTile(const std::string &path, int index) const;

    // Returns total number of tiles in the given tileset
    int getNumTiles(const std::string &path) const;


private:
    int m_tileWidth;
    int m_tileHeight;
    std::map<std::string, sf::Texture> m_textures;
    std::string m_basePath;
};