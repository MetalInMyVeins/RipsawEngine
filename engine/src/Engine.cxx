#include <stdexcept>

#include "RipsawEngine/Core/Engine.hxx"
#include "RipsawEngine/Core/Game.hxx"
#include "RipsawEngine/Managers/BGManager.hxx"
#include "RipsawEngine/Scene/Actor.hxx"
#include "RipsawEngine/Scene/SpriteComponent.hxx"
#include "RipsawEngine/Scene/TransformComponent.hxx"

namespace RipsawEngine
{

Engine::Engine(Game* game, const std::string& wname, int w, int h)
  : mWname{wname},
    mGame{game}
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
  for (auto& manager : mManagers)
  {
    std::visit([](auto* ptr){
        delete ptr;
    }, manager);
  }
  while (!mActors.empty())
  {
    delete mActors.back();
    mActors.pop_back();
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

  SDL_SetHint(SDL_HINT_RENDER_DRIVER, mRendererBackend.c_str());
  
  SDL_CreateWindowAndRenderer(
      mWname.c_str(),
      mScreenWidth, mScreenHeight,
      SDL_WINDOW_FULLSCREEN | SDL_WINDOW_HIGH_PIXEL_DENSITY,
      &mWindow,
      &mRenderer
  );

  if (mWindow == nullptr or mRenderer == nullptr)
  {
    SDL_Log("[ERROR] Failed to set up window and/or renderer");
    return false;
  }

  if (mVsyncEnabled == true)
  {
    if (SDL_SetRenderVSync(mRenderer, 1) == false)
    SDL_Log("[ERROR] Failed to enable vsync");
  }

  SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);

  SDL_PropertiesID props = SDL_GetRendererProperties(mRenderer);
  std::string driver{SDL_GetStringProperty(
      props,
      SDL_PROP_RENDERER_NAME_STRING,
      "unknown"
  )};
  SDL_Log("[INFO] Renderer Backend: %s", driver.c_str());

  if (mGame != nullptr)
  {
    mGame->setEngine(this);
  }
  else
  {
    SDL_Log("[ERROR] Failed to create Game object");
    return false;
  }

  return true;
}

void Engine::run()
{
  mGame->initGame();
  mTimer.start();

  while (mIsRunning)
  {
    this->processInput();
    this->updateEngine();
    mGame->updateGame(mDt);
    this->renderEngine();
    mGame->renderGame();
  }
}

void Engine::shutdown()
{
  mTimer.stop();
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);
  SDL_Quit();
}

void Engine::pauseEngine()
{
  if (mTimer.isRunning())
  {
    if (mTimer.isPaused() == false)
    {
      mTimer.pause();
      SDL_Log("[INFO] Paused");
    }
  }
}

void Engine::resumeEngine()
{
  if (mTimer.isRunning())
  {
    if (mTimer.isPaused() == true)
    {
      mTimer.resume();
      SDL_Log("[INFO] Resumed");
    }
  }
}

void Engine::enginePauseResumeToggle()
{
  if (mTimer.isRunning())
  {
    if (mTimer.isPaused() == false)
    {
      mTimer.pause();
      SDL_Log("[INFO] Paused");
    }
    else
    {
      mTimer.resume();
      SDL_Log("[INFO] Resumed");
    }
  }
}

SDL_Renderer* Engine::getRenderer() const
{
  return mRenderer;
}

std::pair<int, int> Engine::getScreenSize() const
{
  return std::make_pair(mScreenWidth, mScreenHeight);
}

double Engine::getDt() const
{
  return mDt;
}

void Engine::setVsync(bool vsync)
{
  mVsyncEnabled = vsync;
}

void Engine::setRendererBackend(const std::string& backend)
{
  std::vector<std::string> validBackends{"opengl", "vulkan", "software"};

  auto it{std::find(validBackends.begin(), validBackends.end(), backend)};
  if (it == validBackends.end())
  {
    mRendererBackend = "opengl";
  }
  else
  {
    mRendererBackend = backend;
  }
}

Actor* Engine::createActor()
{
  Actor* tempActor{new Actor{this}};
  return tempActor;
}

void Engine::destroyActor(Actor** actor)
{
  if (mActorsBeingUpdated == false)
  {
    this->removeActor(*actor);
    *actor = nullptr;
  }
  else
  {
    mActorsToBeKilled.push_back(actor);
  }
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
    delete *it;
    mActors.erase(it);
  }
  actor = nullptr;
}

void Engine::addSprite(class SpriteComponent* sc)
{
  mSprites.emplace_back(sc);
  SDL_Log("[INFO] Total active sprites++: %ld", mSprites.size());
}

void Engine::removeSprite(SpriteComponent* sprite)
{
  auto it{std::find(mSprites.begin(), mSprites.end(), sprite)};
  if (it != mSprites.end())
  {
    mSprites.erase(it);
  }
  SDL_Log("[INFO] Total active sprites--: %ld", mSprites.size());
}

void Engine::insertActorSpritePair(const std::pair<Actor*, Component*>& asp)
{
  mActorSpritePairs.insert(asp);
}

void Engine::removeActorSpritePair(class Actor* actor)
{
  mActorSpritePairs.erase(actor);
}

BGManager* Engine::createBGManager(const std::vector<std::string>& layers, const std::vector<float>& layerSpeeds)
{
  if (layers.size() != layerSpeeds.size())
  {
    throw std::runtime_error{"BGManager::setSpeeds(): layers should be provided with equal number of speed factors"};
  }

  BGManager* tempBGManager{new BGManager{this, layers, layerSpeeds}};
  mManagers.push_back(tempBGManager);
  return tempBGManager;
}

void Engine::actorGoesBelow(Actor* a1, Actor* a2)
{
  auto it1{std::find(mSprites.begin(), mSprites.end(), mActorSpritePairs[a1])};
  auto it2{std::find(mSprites.begin(), mSprites.end(), mActorSpritePairs[a2])};

  if (it1 < it2)
    return;
  std::rotate(it2, it1, it1 + 1);
}

void Engine::actorGoesAbove(Actor* a1, Actor* a2)
{
  auto it1{std::find(mSprites.begin(), mSprites.end(), mActorSpritePairs[a1])};
  auto it2{std::find(mSprites.begin(), mSprites.end(), mActorSpritePairs[a2])};

  if (it1 > it2)
    return;
  std::rotate(it1, it1 + 1, it2 + 1);
}

}

