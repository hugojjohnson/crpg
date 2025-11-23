#pragma once
#include "../common/TileManager.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>

struct Animation {
  // I must call Animation, hopefully saves me confusion later on.
  std::string tilesetPath;
  std::vector<int> frames; // indexes of frames in the tileset
  float fps = 8.f;
  bool flipHorizontally = false;
};

class AnimationManager {
public:
  explicit AnimationManager(int tileWidth, int tileHeight);

  // Add an animation with a name and frame sequence
  void addAnimation(const std::string &name, const Animation &animation);

  // Switch to another animation (resets to frame 0)
  void play(const std::string &name);

  // Update current animation based on elapsed time
  void update(float deltaTime);

  // Returns the sprite for the current frame
  sf::IntRect getCurrentTexture();

  // Curernt frame
  bool lastFrame() const;

private:
  TileManager m_tileManager;
  std::map<std::string, Animation> m_animations;
  std::string m_current;
  float m_timer = 0.f;
  int m_currentFrame = 0;
};