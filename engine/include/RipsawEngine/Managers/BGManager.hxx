#pragma once

#include <string>
#include <utility>
#include <vector>

#include <glm/glm.hpp>

namespace RipsawEngine
{

class BGManager
{
public:
  /// Constructs BGManager with Engine*, layers of background images, and the speed of each layers.
  /// @details This is a manager class. The purpose of manager classes are to create and manage already-programmed entities to complete a certain task. This background manager class implements parallax scrolling background with layers of provided images and their speeds. The philosophy is, any one-way scrolling 2D infinite background can be implemented with at least two actors. There would be two actors per layer. Each actor of a layer would contain the same layer sprite and would be placed after each other. When an actor goes out of screen bound, they would be repositioned after the next actor creating the illusion of infinite scrolling. The procedure is applied to all layers. And each layer would move at the speed of their respective speed.
  /// @warning Throws runtime error if number of layers and number of speeds doesn't equate.
  /// @param engine Pointer to Engine instance.
  /// @param layers Layers of background images.
  /// @param layerSpeeds Vector of layer speed.
  BGManager(class Engine* engine, const std::vector<std::string>& layers, const std::vector<float>& layerSpeeds);
  /// Implements custom update logic for manager.
  void update();
  /// Sets scrolling speed of layers.
  /// @param speeds Vector of speed values of layers.
  void setSpeeds(const std::vector<float>& speeds);

private:
  /// Pointer to Engine instance.
  class Engine* mEngine{nullptr};
  /// Layers of background images.
  std::vector<std::string> mLayers{};
  /// Speed of background layers.
  std::vector<float> mLayerSpeeds{};
  /// Vector of Actor pairs.
  std::vector<std::pair<class Actor*, class Actor*>> mActorPairs{};
};

}

