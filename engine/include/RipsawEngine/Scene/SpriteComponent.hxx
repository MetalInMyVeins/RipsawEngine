#pragma once

#include <string>
#include <tuple>
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
  /// @param actor Actor owning the component.
  /// @param renderer Renderer.
  /// @param imgfile Path to image file.
  SpriteComponent(class Actor* actor, SDL_Renderer* renderer, const std::string& imgfile);
  /// Constructs sprite component with owning actor, renderer, rectangle size, and color.
  /// @param actor Actor owning the component.
  /// @param renderer Renderer.
  /// @param size Pair of float containing rectangle width and height.
  /// @param color Tuple of RGBA color values.
  SpriteComponent(class Actor* actor, SDL_Renderer* renderer, const std::pair<float, float>& size = {}, const std::tuple<unsigned char, unsigned char, unsigned char, unsigned char>& color = {});
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

