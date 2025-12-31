#pragma once

#include <string>
#include <tuple>
#include <utility>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <glm/glm.hpp>

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
  SpriteComponent(class Actor* actor, SDL_Renderer* renderer, const glm::vec2& size = {}, const std::tuple<unsigned char, unsigned char, unsigned char, unsigned char>& color = {});
  /// Destructs SpriteComponent.
  ~SpriteComponent();
  /// Checks if SpriteComponent is valid.
  bool isComponentValid() const override;
  /// Returns mTexture.
  SDL_Texture* getTexture() const;
  /// Returns texture size.
  glm::vec2 getTexSize() const;
  /// Draws texture on window.
  /// @param dt Delta-time.
  virtual void draw(double dt);
  /// Returns scale of texture.
  float getScale() const;
  /// Sets scale of texture.
  /// @param scale Texture scale.
  void setScale(float scale);
  /// Returns amount of rotation mRotationAmount.
  double getRotationAmount() const;
  /// Sets rotation speed mRotationSpeed.
  /// @param rotation Rotation speed per second in degrees by which rotation amount would be incremented/decremented.
  void setRotationSpeed(double rotation);
  /// Rotates sprite clockwise by specified degrees.
  /// @param degrees Angle in degrees by which sprite would be rotated.
  void rotateClockwiseAmount(double degrees);
  /// Rotates sprite anti-clockwise by specified degrees.
  /// @param degrees Angle in degrees by which sprite would be rotated.
  void rotateAntiClockwiseAmount(double degrees);
  /// Flips sprite horizontally unless any rotation has occurred.
  void flipHorizontally();
  /// Flips sprite vertically unless any rotation has occurred.
  void flipVertically();
  /// Sets flip state to default.
  void flipDefault();

public:
  /// Fits sprite covering entire screen preserving aspect ratio.
  void fitByAspectRatio();
  /// Normalizes angle in [0, 360) range.
  /// @param degrees Angle in degrees to be normalized.
  void normalizeDegrees(double& degrees);

private:
  /// Renderer.
  SDL_Renderer* mRenderer{nullptr};
  /// Image file path.
  std::string mImgFile{};
  /// Main texture.
  SDL_Texture* mTexture{nullptr};
  /// Texture size.
  glm::vec2 mTexSize{};
  /// Modified texture dimension after scale change.
  glm::vec2 mTexSizeDynamic{};
  /// Texture scale.
  float mScale{1.f};
  /// Speed of rotation (degree) controlling how fast to rotate sprite.
  double mRotationSpeed{0};
  /// The amount of rotation (degree) to take effect in texture.
  double mRotationAmount{0};
  /// Boolean flag to track if sprite has rotated.
  bool mHasRotated{false};
  /// Current flip state of sprite.
  SDL_FlipMode mFlipState{SDL_FLIP_NONE};
};

}

