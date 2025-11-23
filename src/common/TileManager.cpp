#include "../../include/common/TileManager.hpp"
#include <stdexcept>

TileManager::TileManager(int tileWidth, int tileHeight)
    : m_tileWidth(tileWidth), m_tileHeight(tileHeight) {
}

void TileManager::loadIfNeeded(const std::string& path) {
    // If already cached, you're done
    if (m_spriteCache.contains(path)) {
        return;
    }

    // Load texture
    sf::Texture texture;

    if (!texture.loadFromFile(m_basePath + path)) {
        throw std::runtime_error("TileManager: Failed to load tileset: " + path);
    }

    // Store texture so its lifetime covers all sprites referencing it
    m_textureCache[path] = std::move(texture);
    sf::Texture& texRef = m_textureCache[path];

    const int texW = texRef.getSize().x;
    const int texH = texRef.getSize().y;

    const int cols = texW / m_tileWidth;
    const int rows = texH / m_tileHeight;

    if (cols <= 0 || rows <= 0) {
        throw std::runtime_error("TileManager: Invalid tileset size: " + path);
    }

    const int totalTiles = cols * rows;

    // Pre-slice every tile
    std::vector<sf::Sprite> tiles;
    tiles.reserve(totalTiles);

    for (int i = 0; i < totalTiles; i += 1) {
        const int x = (i % cols) * m_tileWidth;
        const int y = (i / cols) * m_tileHeight;

        sf::Sprite sprite{texRef};
        sprite.setTextureRect(sf::IntRect({x, y}, {m_tileWidth, m_tileHeight}));

        tiles.push_back(sprite);
    }

    m_spriteCache[path] = std::move(tiles);
}

const sf::Sprite& TileManager::getTile(const std::string& path, int index) {
    loadIfNeeded(path);

    auto& tiles = m_spriteCache[path];

    if (index < 0 || index >= static_cast<int>(tiles.size())) {
        throw std::out_of_range("TileManager: tile index out of range");
    }

    return tiles[index];
}


int TileManager::getNumTiles(const std::string& path) {
    loadIfNeeded(path);
    return static_cast<int>(m_spriteCache[path].size());
}
