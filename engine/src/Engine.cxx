#include "RipsawEngine/Core/Engine.hxx"
#include "RipsawEngine/Scene/Actor.hxx"
#include "RipsawEngine/Scene/TransformComponent.hxx"

namespace RipsawEngine
{

Engine::Engine(int w, int h)
{
  if (w != 0 and h != 0)
  {
    mIsDisplaySetManually = true;
    mScreenWidth = w;
    mScreenHeight = h;
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
    if (count < 1 and displays == nullptr)
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

  SDL_CreateWindowAndRenderer("Starship", mScreenWidth, mScreenHeight, SDL_WINDOW_FULLSCREEN, &mWindow, &mRenderer);
  SDL_SetRenderVSync(mRenderer, 1);
  this->loadMedia();
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
  this->unloadMedia();
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);
  SDL_Quit();
}

void Engine::addActor(Actor* actor)
{
  mActors.emplace_back(actor);
}

void Engine::removeActor(Actor* actor)
{}

bool Engine::loadMedia()
{
  return true;
}

void Engine::unloadMedia()
{
  for (const auto& actor : mActors)
  {
    delete actor;
  }
}

}

