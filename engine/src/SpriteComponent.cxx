#include <cmath>

#include "RipsawEngine/Core/Core.hxx"
#include "RipsawEngine/Scene/Actor.hxx"
#include "RipsawEngine/Scene/SpriteComponent.hxx"
#include "RipsawEngine/Scene/TransformComponent.hxx"

namespace RipsawEngine
{

SpriteComponent::SpriteComponent(Actor* actor, SDL_Renderer* renderer, const std::string& imgfile)
  : Component{actor},
    mRenderer{renderer},
    mImgFile{imgfile}
{
  mOwner->helperRegisterComponent("SpriteComponent");
  mOwner->setSpriteComponent(this);

  SDL_Surface* surface{IMG_Load(mImgFile.c_str())};
  if (surface != nullptr)
  {
    mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
  }
  SDL_DestroySurface(surface);

  if (mTexture != nullptr)
  {
    float w{}, h{};
    SDL_GetTextureSize(mTexture, &w, &h);
    mTexSize = {w, h};
  }

  if (this->isComponentValid())
  {
    SDL_Log("[INFO] Component added: SpriteComponent: %p to Actor: %p", static_cast<void*>(this), static_cast<void*>(mOwner));
    SDL_Log("\tTexture size: %.2f X %.2f", static_cast<double>(mTexSize.x), static_cast<double>(mTexSize.y));
    mOwner->getEngine()->addSprite(this);
  }
  else
  {
    SDL_Log("[ERROR] SpriteComponent construction FAILED");
  }
}

SpriteComponent::SpriteComponent(class Actor* actor, SDL_Renderer* renderer, const glm::vec2& size, const std::tuple<unsigned char, unsigned char, unsigned char, unsigned char>& color)
  : Component{actor},
    mRenderer{renderer}
{
  mOwner->helperRegisterComponent("SpriteComponent");
  mOwner->setSpriteComponent(this);

  SDL_Surface* surface{SDL_CreateSurface(static_cast<int>(size.x), static_cast<int>(size.y), SDL_PIXELFORMAT_RGBA8888)};
  Uint32 col{SDL_MapSurfaceRGBA(surface, std::get<0>(color), std::get<1>(color), std::get<2>(color), std::get<3>(color))};
  SDL_FillSurfaceRect(surface, nullptr, col);
  if (surface != nullptr)
  {
    mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
  }
  SDL_DestroySurface(surface);
  
  if (mTexture != nullptr)
  {
    float w{}, h{};
    SDL_GetTextureSize(mTexture, &w, &h);
    mTexSize = {w, h};
  }

  if (this->isComponentValid())
  {
    SDL_Log("[INFO] Component added: SpriteComponent: %p to Actor: %p", static_cast<void*>(this), static_cast<void*>(mOwner));
    SDL_Log("\tTexture size: %.2f X %.2f", static_cast<double>(mTexSize.x), static_cast<double>(mTexSize.y));
    mOwner->getEngine()->addSprite(this);
  }
  else
  {
    SDL_Log("[ERROR] SpriteComponent construction FAILED");
  }
}

SpriteComponent::~SpriteComponent()
{
  mOwner->deregisterComponent("SpriteComponent");
  SDL_DestroyTexture(mTexture);
  mOwner->getEngine()->removeSprite(this);
}

bool SpriteComponent::isComponentValid() const
{
  bool isValid{true};
  if (mRenderer == nullptr)
    isValid = false;
  if (mTexture == nullptr)
    isValid = false;
  return isValid;
}

SDL_Texture* SpriteComponent::getTexture() const
{
  return mTexture;
}

glm::vec2 SpriteComponent::getTexSize() const
{
  return {mTexSize.x * mScale, mTexSize.y * mScale};
}

void SpriteComponent::draw(double dt)
{
  mRotationAmount += mRotationSpeed * dt;
  this->normalizeDegrees(mRotationAmount);

  SDL_FRect rect
  {
    mOwner->getTransformComponent()->getPosition().x - mTexSize.x * mScale / 2.f,
    mOwner->getTransformComponent()->getPosition().y - mTexSize.y * mScale / 2.f,
    mTexSize.x * mScale,
    mTexSize.y * mScale
  };
  if (!SDL_RenderTextureRotated(mRenderer, mTexture, nullptr, &rect, mRotationAmount, nullptr, mFlipState))
  {
    SDL_Log("[ERROR] Draw failed on SpriteComponent: %p", static_cast<void*>(this));
  }
}

float SpriteComponent::getScale() const
{
  return mScale;
}

void SpriteComponent::setScale(float scale)
{
  mScale = scale;
  mTexSizeDynamic.x = mTexSize.x * scale;
  mTexSizeDynamic.y = mTexSize.y * scale;
  SDL_Log("[INFO] SpriteComponent: %p scaled by %.2fx: %.2f X %.2f", static_cast<void*>(this), static_cast<double>(scale), static_cast<double>(mTexSizeDynamic.x), static_cast<double>(mTexSizeDynamic.y));
}

double SpriteComponent::getRotationAmount() const
{
  return mRotationAmount;
}

double SpriteComponent::getRotationSpeed()
{
  return mRotationSpeed;
}

void SpriteComponent::setRotationSpeed(double rotation)
{
  mRotationSpeed = rotation;

  if (rotation != 0.0)
  {
    mHasRotated = true;
  }
}

void SpriteComponent::rotateClockwiseAmount(double degrees)
{
  if (degrees < 0)
  {
    SDL_Log("[ERROR] Clockwise degree amount should be positive");
    return;
  }

  mRotationAmount += degrees;
  this->normalizeDegrees(mRotationAmount);
  mHasRotated = true;
}

void SpriteComponent::rotateAntiClockwiseAmount(double degrees)
{
  if (degrees < 0)
  {
    SDL_Log("[ERROR] Anti-Clockwise degree amount should be positive");
    return;
  }

  mRotationAmount -= degrees;
  this->normalizeDegrees(mRotationAmount);
  mHasRotated = true;
}
  
void SpriteComponent::flipHorizontally()
{
  if (mHasRotated == true)
  {
    SDL_Log("[ERROR] Cannot flip after rotation");
    return;
  }

  mFlipState = SDL_FLIP_HORIZONTAL;
}
  
void SpriteComponent::flipVertically()
{
  if (mHasRotated == true)
  {
    SDL_Log("[ERROR] Cannot flip after rotation");
    return;
  }

  mFlipState = SDL_FLIP_VERTICAL;
}
  
void SpriteComponent::flipDefault()
{
  if (mHasRotated == true)
  {
    SDL_Log("[ERROR] Cannot flip after rotation");
    return;
  }

  mFlipState = SDL_FLIP_NONE;
}

void SpriteComponent::changeCoord([[maybe_unused]] const glm::ivec2& coord)
{}

void SpriteComponent::setRotationAmount(double rotationAmount)
{
  mRotationAmount = rotationAmount;
}
 
SDL_Renderer* SpriteComponent::getRenderer() const
{
  return mRenderer;
}

SDL_FlipMode SpriteComponent::getFlipState() const
{
  return mFlipState;
}

void SpriteComponent::fitByAspectRatio()
{
  SDL_Log("[INFO] SpriteComponent: %p fitting by aspect ratio", static_cast<void*>(this));
  float sw{static_cast<float>(mOwner->getEngine()->getScreenSize().first)};
  float sh{static_cast<float>(mOwner->getEngine()->getScreenSize().second)};
  float ratw{sw / mTexSize.x};
  float rath{sh / mTexSize.y};
  float ratbig{(ratw >= rath) ? ratw : rath};
  this->setScale(ratbig);
}

void SpriteComponent::normalizeDegrees(double& degrees)
{
  degrees = fmod(degrees, 360.0);
  if (degrees < 0.0)
    degrees += 360.0;
}

}

