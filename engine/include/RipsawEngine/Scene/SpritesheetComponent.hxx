#pragma once

#include <string>

#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include "RipsawEngine/Scene/SpriteComponent.hxx"

namespace RipsawEngine
{

class SpritesheetComponent : public SpriteComponent
{
public:
  /// Constructs spritesheet component with owning actor, renderer, spritesheet image, dimension of spritesheet, and default rendering coordinate of spritesheet. 
  /// @param actor Actor owning the component.
  /// @param renderer Renderer.
  /// @param imgfile Path to image file.
  /// @param dims Dimension of spritesheet.
  /// @param defaultCoord Default coordinate of spritesheet.
  SpritesheetComponent(class Actor* actor, SDL_Renderer* renderer, const std::string& imgfile, const glm::vec2& dims, const glm::vec2& defaultCoord = {1, 1});
  /// Draws texture on window.
  /// @param dt Delta-time.
  void draw(double dt) override;
  /// Changes default coordinate of spritesheet.
  void changeCoord(const glm::vec2& coord) override;

private:
  /// Dimension of spritesheet in {col, row} where col is number of sprites horizontally, and row is number of sprites vertically.
  glm::vec2 mDims{};
  /// Default coordinate of spritesheet.
  glm::vec2 mDefaultCoord{1, 1};
};

}

