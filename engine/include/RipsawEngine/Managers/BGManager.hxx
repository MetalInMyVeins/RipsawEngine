#pragma once

#include <string>
#include <tuple>
#include <vector>

namespace RipsawEngine
{

class BGManager
{
public:
  /// Constructs BGManager with Engine*, background image layers, and the speed of each layers.
  /// @details This is a manager class. The purpose of manager classes are to create and manage already-programmed entities to complete a certain task. This background manager class implements parallax scrolling background with layers of provided images and their speeds. The philosophy is, any both-way scrolling 2D infinite background can be implemented with at least three actors. So, there would be a triplet of actors per layer which would be placed side by side to each other. The middle actor would be placed at the center of the screen, right one to its right, and left one to its left. Each actor would receive the same layer sprite. When the middle actor would go out of screen bound, its left or right actor would be repositioned to the right or left depending on scroll direction creating the illusion of infinite scrolling. The procedure is applied to all layers. And each layer would move at the speed of their respective speed.
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
  /// Vector of Actor triplet.
  std::vector<std::tuple<class Actor*, class Actor*, class Actor*>> mActorTriplets{};
};

}

