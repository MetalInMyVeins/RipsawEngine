#pragma once

#include <string>
#include <utility>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Component.hxx"

namespace RipsawEngine
{

class SpriteComponent : public RipsawEngine::Component
{
public:
  /// Constructs sprite component with owning actor, renderer, and image file.
  /// @brief Constructs transform component with owning actor, position, and velocity.
  /// @param actor Actor owning the component.
  /// @param renderer Renderer.
  /// @param imgfile Path to image file.
  SpriteComponent(class Actor* actor, SDL_Renderer* renderer, const std::string& imgfile);
  /// Destructs SpriteComponent.
  ~SpriteComponent();
  /// Checks if SpriteComponent is valid.
  bool isComponentValid() const override;
  /// Returns mTexture.
  SDL_Texture* getTexture() const;
  /// Returns texture size.
  std::pair<int, int> getTexSize() const;
  /// Draws texture on window.
  virtual void draw();
  /// Returns scale of texture.
  float getScale() const;
  /// Sets scale of texture.
  /// @param scale Texture scale.
  void setScale(float scale);

private:
  /// Renderer.
  SDL_Renderer* mRenderer{nullptr};
  /// Image file path.
  std::string mImgFile{};
  /// Main texture.
  SDL_Texture* mTexture{nullptr};
  /// Texture size.
  std::pair<float, float> mTexSize{};
  /// Texture scale.
  float mScale{1.f};
};

}

