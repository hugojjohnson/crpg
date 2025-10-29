#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TileManager {
public:
    explicit TileManager(int tileWidth, int tileHeight, std::string basePath);

    // Returns a sprite for a given tile index.
    // Automatically loads the texture if it isn’t already loaded.
    sf::Sprite getTile(const std::string &path, int index);

    // Returns total number of tiles in the given tileset
    int getNumTiles(const std::string &path);


private:
    int m_tileWidth;
    int m_tileHeight;
    std::map<std::string, sf::Texture> m_textures;
    std::string m_basePath;

    // load a tileset from the path specified
    bool loadIfNeeded(const std::string &path);
};