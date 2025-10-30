#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "TileManager.hpp"
#include "TileDrawer.hpp"
#include "external/nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

class TileSerialiser {
public:
    // Save the tile map to a JSON file
    static void save(const std::string &path,
                     const std::unordered_map<std::string, TileDrawer::TileInfo> &tileMap);

    // Load a tile map from JSON using a TileManager
    static void load(const std::string &path, TileDrawer &tileDrawer);
};
