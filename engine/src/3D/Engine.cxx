#include "RipsawEngine/3D/Core/Engine.hxx"

#include <stdexcept>

namespace RipsawEngine
{

void Engine::init()
{
  bool status = SDL_Init(SDL_INIT_VIDEO);
  if (status == false)
    throw std::runtime_error{"[ERROR] SDL3 initialization failure"};

  SDL_DisplayID did = SDL_GetPrimaryDisplay();
  const SDL_DisplayMode* dm = SDL_GetCurrentDisplayMode(did);
  mWidth = dm->w;
  mHeight = dm->h;
  if (mWidth <= 0 or mHeight <= 0)
    throw std::runtime_error{"[ERROR] Invalid display dimension"};
  SDL_Log("[INFO] Detected display dimension: %d X %d", mWidth, mHeight);
}

}

