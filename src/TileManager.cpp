#include "../include/TileManager.hpp"
#include <iostream>

TileManager::TileManager(int tileWidth, int tileHeight, std::string basePath)
    : m_tileWidth(tileWidth), m_tileHeight(tileHeight), m_basePath(basePath) {}

bool TileManager::loadTileSet(const std::string &path) {
    if (m_textures.contains(path)) {
        // Already loaded
        return true;
    }

    sf::Texture texture;
    if (!texture.loadFromFile(m_basePath + path)) {
        std::cerr << "Failed to load tileset: " << path << '\n';
        return false;
    }

    // Store texture in map (move semantics to avoid copy)
    m_textures.emplace(path, std::move(texture));
    return true;
}

sf::Sprite TileManager::getTile(const std::string &path, int index) const {
    auto it = m_textures.find(path);
    if (it == m_textures.end()) {
        std::cerr << "Tileset not loaded: " << path << '\n';
        throw new std::runtime_error("Tileset not loaded");
    }

    const sf::Texture &texture = it->second;
    int cols = texture.getSize().x / m_tileWidth;
    int x = (index % cols) * m_tileWidth;
    int y = (index / cols) * m_tileHeight;

    sf::Sprite sprite(texture);
    sprite.setTextureRect(sf::IntRect({x, y}, {m_tileWidth, m_tileHeight}));
    return sprite;
}


int TileManager::getNumTiles(const std::string &path) const {
    auto it = m_textures.find(path);
    if (it == m_textures.end()) {
        std::cerr << "Tileset not loaded: " << path << '\n';
        return 0;
    }

    const sf::Texture &texture = it->second;
    int cols = texture.getSize().x / m_tileWidth;
    int rows = texture.getSize().y / m_tileHeight;
    return cols * rows;
}