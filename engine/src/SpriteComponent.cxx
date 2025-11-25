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
    SDL_Log("[INFO] SpriteComponent created: %p", (void*)this);
    SDL_Log("\tAdded to Actor: %p", (void*)mOwner);
    SDL_Log("\tTexture size: %.f X %.f", mTexSize.first, mTexSize.second);
    mOwner->getEngine()->addSprite(this);
  }
  else
  {
    SDL_Log("[ERROR] SpriteComponent construction FAILED");
  }
}

SpriteComponent::~SpriteComponent()
{
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

std::pair<int, int> SpriteComponent::getTexSize() const
{
  return mTexSize;
}

void SpriteComponent::draw()
{
  SDL_FRect rect
  {
    mOwner->getTransformComponent()->getPosition().x - mTexSize.first / 2.f,
    mOwner->getTransformComponent()->getPosition().y - mTexSize.second / 2.f,
    mTexSize.first * mScale,
    mTexSize.second * mScale
  };
  SDL_RenderTexture(mRenderer, mTexture, nullptr, &rect);
}

float SpriteComponent::getScale() const
{
  return mScale;
}

void SpriteComponent::setScale(float scale)
{
  mScale = scale;
}

}

