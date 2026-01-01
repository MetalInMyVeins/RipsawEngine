#include "RipsawEngine/Scene/Actor.hxx"
#include "RipsawEngine/Scene/SpritesheetComponent.hxx"
#include "RipsawEngine/Scene/TransformComponent.hxx"

namespace RipsawEngine
{

SpritesheetComponent::SpritesheetComponent(Actor* actor, SDL_Renderer* renderer, const std::string& imgfile, const glm::vec2& dims, const glm::vec2& defaultCoord)
  : SpriteComponent{actor, renderer, imgfile},
    mDims{dims},
    mDefaultCoord{defaultCoord}
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
  SpriteComponent::setRotationAmount(rotationAmount);
  SpriteComponent::normalizeDegrees(rotationAmount);
  SDL_Texture* texture{SpriteComponent::getTexture()};
  glm::vec2 texSize{SpriteComponent::getTexSize()};
  float scale{SpriteComponent::getScale()};
  
  SDL_FRect srcrect
  {
    texSize.x / mDims.x * (mDefaultCoord.x - 1),
    texSize.y / mDims.y * (mDefaultCoord.y - 1),
    texSize.x / mDims.x,
    texSize.y / mDims.y
  };
  SDL_FRect dstrect
  {
    mOwner->getTransformComponent()->getPosition().x - texSize.x / mDims.x * scale / 2.f,
    mOwner->getTransformComponent()->getPosition().y - texSize.y / mDims.y * scale / 2.f,
    texSize.x / mDims.x * scale,
    texSize.y / mDims.y * scale
  };
  if (!SDL_RenderTextureRotated(SpriteComponent::getRenderer(), texture, &srcrect, &dstrect, rotationAmount, nullptr, SpriteComponent::getFlipState()))
  {
    SDL_Log("[ERROR] Draw failed on SpritesheetComponent: %p", (void*)this);
  }
}

void SpritesheetComponent::changeCoord(const glm::vec2& coord)
{
  mDefaultCoord = coord;
}

}

