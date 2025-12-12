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
    SDL_Log("\tTexture size: %.f X %.f", mTexSize.first, mTexSize.second);
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

