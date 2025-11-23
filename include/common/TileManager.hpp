#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <vector>

class TileManager {
public:
    explicit TileManager(int tileWidth, int tileHeight);

    // Returns a cached sprite for the given tile index.
    const sf::Sprite& getTile(const std::string& path, int index);

    // Returns the number of tiles in the cached tileset
    int getNumTiles(const std::string& path);

private:
    int m_tileWidth;
    int m_tileHeight;
    std::string m_basePath = "assets/sprites/";

    // path → vector of prebuilt tiles
    std::unordered_map<std::string, std::vector<sf::Sprite>> m_spriteCache;

    // path → textures (must keep them alive for sprites!)
    std::unordered_map<std::string, sf::Texture> m_textureCache;

    void loadIfNeeded(const std::string& path);
};
