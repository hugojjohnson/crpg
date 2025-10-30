#include "../../include/common/TileSerialiser.hpp"

void TileSerialiser::save(const std::string &path, const std::unordered_map<std::string, BackgroundManager::TileInfo> &tileMap) {
  json tileMapJson = json::array();

  for (const auto &pair : tileMap) {
    const BackgroundManager::TileInfo &sprite = pair.second;
    const auto name = pair.first;

    // Recover x, y tile coordinates from the sprite position
    int x = static_cast<int>(sprite.sprite.getPosition().x / sprite.sprite.getTextureRect().size.x);
    int y = static_cast<int>(sprite.sprite.getPosition().y / sprite.sprite.getTextureRect().size.y);

    // Recover tileset path and index from sprite's texture (we’ll assume stored via userData or separate mapping)
    // For simplicity, let’s assume the texture’s file path is stored in the sprite’s texture pointer map elsewhere
    // We'll require you have a mapping: texture pointer -> path
    const sf::Texture &tex = sprite.sprite.getTexture();

    // Example placeholder: in practice, you need BackgroundManager to keep track of index/path per sprite
    std::cout << sprite.path << "\n";
    tileMapJson.push_back({{"x", x}, {"y", y}, {"tileset", sprite.path}, {"index", sprite.index}});
  }

  std::ofstream outFile(path);
  if (!outFile.is_open()) {
    std::cerr << "Failed to open file for saving: " << path << "\n";
    return;
  }

  outFile << tileMapJson.dump(4);
}

void TileSerialiser::load(const std::string &path, BackgroundManager &BackgroundManager) {
  std::ifstream inFile(path);
  if (!inFile.is_open()) {
    std::cerr << "Failed to open file for loading: " << path << "\n";
    return;
  }

  std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
  std::cout << "Raw file content:\n" << content << "\n";
  json loaded = json::parse(content);
  std::cout << "Loaded JSON size: " << loaded.size() << "\n";

  for (auto &tile : loaded) {
    std::cout << "Niceee\n";
    int x = tile["x"];
    int y = tile["y"];
    std::string tilesetPath = tile["tileset"];
    int index = tile["index"];
    std::cout << "(" << x << ", " << y << ")\n";
    std::cout << tilesetPath << " " << index << "\n";

    sf::Sprite sprite = BackgroundManager.m_tileManager.getTile(tilesetPath, index);
    sprite.setPosition({static_cast<float>(x * sprite.getTextureRect().size.x), static_cast<float>(y * sprite.getTextureRect().size.y)});

    // Encode key as before
    std::string key = std::to_string(x) + "," + std::to_string(y);
    BackgroundManager.m_tileMap.emplace(key, BackgroundManager::TileInfo{std::move(sprite), tilesetPath, index});
  }
}
