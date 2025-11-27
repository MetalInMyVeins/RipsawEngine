#include "RipsawEngine/Core/Engine.hxx"
#include "RipsawEngine/Scene/Actor.hxx"
#include "RipsawEngine/Scene/SpriteComponent.hxx"
#include "RipsawEngine/Scene/TransformComponent.hxx"

namespace RipsawEngine
{

Engine::Engine(const std::string& wname, int w, int h)
  : mWname{wname}
{
  if (w != 0 and h != 0)
  {
    mIsDisplaySetManually = true;
    mScreenWidth = w;
    mScreenHeight = h;
  }
}

Engine::~Engine()
{
  for (const auto& actor : mActors)
  {
    if (actor != nullptr)
      delete actor;
  }
}

bool Engine::init()
{
  if (SDL_Init(SDL_INIT_VIDEO) == false)
  {
    SDL_Log("[ERROR] SDL_INIT_VIDEO failed");
    return false;
  }

  if (TTF_Init() == false)
  {
    SDL_Log("[ERROR] TTF_Init failed");
    return false;
  }
  
  if (mIsDisplaySetManually == false)
  {
    int count{};
    SDL_DisplayID* displays{SDL_GetDisplays(&count)};
    if (displays == nullptr or count == 0)
    {
      SDL_Log("[ERROR] Couldn't get display");
      return false;
    }

    SDL_DisplayID dID{displays[0]};
    const SDL_DisplayMode* dm{SDL_GetCurrentDisplayMode(dID)};
    if (dm == nullptr)
    {
      SDL_Log("[ERROR] Failed to set up display");
      return false;
    }
    SDL_Log("[INFO] Display ID: %d", dID);
    SDL_Log("[INFO] Display Mode: %p", (void*)dm);
    mScreenWidth = dm->w;
    mScreenHeight = dm->h;
    SDL_free(displays);
  }
  SDL_Log("[INFO] Display Resolution: %d X %d", mScreenWidth, mScreenHeight);

  SDL_SetHint(SDL_HINT_RENDER_DRIVER, "vulkan");
  
  SDL_CreateWindowAndRenderer(
      mWname.c_str(),
      mScreenWidth, mScreenHeight,
      SDL_WINDOW_FULLSCREEN | SDL_WINDOW_HIGH_PIXEL_DENSITY,
      &mWindow,
      &mRenderer
  );
  
  SDL_SetRenderVSync(mRenderer, 1);
  SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);

  return true;
}

void Engine::run()
{
  while (mIsRunning)
  {
    this->processInput();
    this->updateEngine();
    this->renderEngine();
  }
}

void Engine::shutdown()
{
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);
  SDL_Quit();
}

SDL_Renderer* Engine::getRenderer() const
{
  return mRenderer;
}

std::pair<int, int> Engine::getScreenSize() const
{
  return std::make_pair(mScreenWidth, mScreenHeight);
}

void Engine::addActor(Actor* actor)
{
  mActors.emplace_back(actor);
  mTotalActorsSize += sizeof(*actor);
  SDL_Log("[INFO] Cumulative actor size: %ld bytes", mTotalActorsSize);
}

void Engine::removeActor(Actor* actor)
{
  auto it{std::find(mActors.begin(), mActors.end(), actor)};
  if (it != mActors.end())
  {
    mActors.erase(it);
  }
}

void Engine::addSprite(class SpriteComponent* sc)
{
  mSprites.emplace_back(sc);
  SDL_Log("[INFO] Total active sprites: %ld", mSprites.size());
}

void Engine::removeSprite(SpriteComponent* sprite)
{
  auto it{std::find(mSprites.begin(), mSprites.end(), sprite)};
  if (it != mSprites.end())
  {
    mSprites.erase(it);
  }
  SDL_Log("[INFO] Total active sprites: %ld", mSprites.size());
}

}

