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
    mTexSize = std::make_pair(mTexture->w, mTexture->h);
  }

  if (this->isComponentValid())
  {
    SDL_Log("[INFO] Component added: SpriteComponent: %p to Actor: %p", (void*)this, (void*)mOwner);
    SDL_Log("\tTexture size: %.2f X %.2f", mTexSize.first, mTexSize.second);
    mOwner->getEngine()->addSprite(this);
  }
  else
  {
    SDL_Log("[ERROR] SpriteComponent construction FAILED");
  }
}

SpriteComponent::SpriteComponent(class Actor* actor, SDL_Renderer* renderer, const std::pair<float, float>& size, const std::tuple<unsigned char, unsigned char, unsigned char, unsigned char>& color)
  : Component{actor},
    mRenderer{renderer}
{
  mOwner->helperRegisterComponent("SpriteComponent");

  mOwner->setSpriteComponent(this);

  SDL_Surface* surface{SDL_CreateSurface(size.first, size.second, SDL_PIXELFORMAT_RGBA8888)};
  Uint32 col{SDL_MapSurfaceRGBA(surface, std::get<0>(color), std::get<1>(color), std::get<2>(color), std::get<3>(color))};
  SDL_FillSurfaceRect(surface, nullptr, col);
  if (surface != nullptr)
  {
    mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
  }
  SDL_DestroySurface(surface);
  
  if (mTexture != nullptr)
  {
    mTexSize = std::make_pair(mTexture->w, mTexture->h);
  }

  if (this->isComponentValid())
  {
    SDL_Log("[INFO] Component added: SpriteComponent: %p to Actor: %p", (void*)this, (void*)mOwner);
    SDL_Log("\tTexture size: %.2f X %.2f", mTexSize.first, mTexSize.second);
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

std::pair<float, float> SpriteComponent::getTexSize() const
{
  return {mTexSize.first * mScale, mTexSize.second * mScale};
}

void SpriteComponent::draw()
{
  if (mRotationAmount >= 360.0)
  {
    mRotationAmount = 0.0;
  }

  SDL_FRect rect
  {
    mOwner->getTransformComponent()->getPosition().x - mTexSize.first * mScale / 2.f,
    mOwner->getTransformComponent()->getPosition().y - mTexSize.second * mScale / 2.f,
    mTexSize.first * mScale,
    mTexSize.second * mScale
  };
  if (!SDL_RenderTextureRotated(mRenderer, mTexture, nullptr, &rect, mRotationAmount, nullptr, SDL_FLIP_NONE))
  {
    SDL_Log("[ERROR] Draw failed on SpriteComponent: %p", (void*)this);
  }

  mRotationAmount += mRotationSpeed * mOwner->getEngine()->getDt();
}

float SpriteComponent::getScale() const
{
  return mScale;
}

void SpriteComponent::setScale(float scale)
{
  mScale = scale;
  mTexSizeDynamic.first = mTexSize.first * scale;
  mTexSizeDynamic.second = mTexSize.second * scale;
  SDL_Log("[INFO] SpriteComponent: %p scaled by %.2fx: %.2f X %.2f", (void*)this, scale, mTexSizeDynamic.first, mTexSizeDynamic.second);
}

double SpriteComponent::getRotationAmount() const
{
  return mRotationAmount;
}

void SpriteComponent::setRotationSpeed(double rotation)
{
  mRotationSpeed = rotation;
}

void SpriteComponent::fitByAspectRatio()
{
  SDL_Log("[INFO] SpriteComponent: %p fitting by aspect ratio", (void*)this);
  float sw{static_cast<float>(mOwner->getEngine()->getScreenSize().first)};
  float sh{static_cast<float>(mOwner->getEngine()->getScreenSize().second)};
  float ratw{sw / mTexSize.first};
  float rath{sh / mTexSize.second};
  float ratbig{(ratw >= rath) ? ratw : rath};
  this->setScale(ratbig);
}

}

