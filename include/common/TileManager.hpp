#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TileManager {
public:
    explicit TileManager(int tileWidth, int tileHeight);

    // Returns a sprite for a given tile index.
    // Automatically loads the texture if it isn’t already loaded.
    sf::Sprite getTile(const std::string &path, int index);

    // Returns total number of tiles in the given tileset
    int getNumTiles(const std::string &path);


private:
    int m_tileWidth;
    int m_tileHeight;
    std::string m_basePath = "assets/sprites/";
    std::map<std::string, sf::Texture> m_textures;

    // load a tileset from the path specified
    bool loadIfNeeded(const std::string &path);
};