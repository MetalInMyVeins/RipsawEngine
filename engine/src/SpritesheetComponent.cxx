#include "RipsawEngine/Core/Engine.hxx"
#include "RipsawEngine/Scene/Actor.hxx"
#include "RipsawEngine/Scene/SpritesheetComponent.hxx"
#include "RipsawEngine/Scene/TransformComponent.hxx"

namespace RipsawEngine
{

SpritesheetComponent::SpritesheetComponent(Actor* actor, SDL_Renderer* renderer, const std::string& imgfile, const glm::ivec2& dims, const glm::ivec2& defaultCoord, bool doAnimate, float animFPS)
  : SpriteComponent{actor, renderer, imgfile},
    mDims{dims},
    mDefaultCoord{defaultCoord},
    mDoAnimate{doAnimate},
    mAnimFPS{animFPS}
{
  if (defaultCoord.x > mDims.x or defaultCoord.x < 1 or defaultCoord.y > mDims.y or defaultCoord.y < 1)
  {
    SDL_Log("[ERROR] Invalid spritesheet coordinate, defaulted to {1, 1}");
    mDefaultCoord = {1, 1};
  }
}

void SpritesheetComponent::draw(double dt)
{
  double rotationAmount{SpriteComponent::getRotationAmount()};
  double rotationSpeed{SpriteComponent::getRotationSpeed()};
  rotationAmount += rotationSpeed * dt;
  SpriteComponent::normalizeDegrees(rotationAmount);
  SpriteComponent::setRotationAmount(rotationAmount);
  SDL_Texture* texture{SpriteComponent::getTexture()};
  glm::vec2 texSize{SpriteComponent::getTexSize()};
  float scale{SpriteComponent::getScale()};
  float texw{texSize.x / mDims.x};
  float texh{texSize.y / mDims.y};

  if (mDoAnimate == true)
  {
    mCurrentFrame += mAnimFPS * dt;
    int frame{static_cast<int>(mCurrentFrame)};
    if (frame >= mDims.x)
    {
      mDefaultCoord.x = 1;
      mCurrentFrame = 1;
    }
    else
      mDefaultCoord.x = frame;
  }

  SDL_FRect srcrect
  {
    texw * (mDefaultCoord.x - 1),
    texh * (mDefaultCoord.y - 1),
    texw,
    texh
  };
  SDL_FRect dstrect
  {
    mOwner->getTransformComponent()->getPosition().x - texw * scale / 2.f,
    mOwner->getTransformComponent()->getPosition().y - texh * scale / 2.f,
    texw * scale,
    texh * scale
  };
  if (!SDL_RenderTextureRotated(SpriteComponent::getRenderer(), texture, &srcrect, &dstrect, rotationAmount, nullptr, SpriteComponent::getFlipState()))
  {
    SDL_Log("[ERROR] Draw failed on SpritesheetComponent: %p", (void*)this);
  }
}

void SpritesheetComponent::changeCoord(const glm::ivec2& coord)
{
  mDefaultCoord = coord;
}

}

