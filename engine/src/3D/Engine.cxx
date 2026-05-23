#include "RipsawEngine/3D/Core/Engine.hxx"

#include <stdexcept>

namespace RipsawEngine
{

Engine::Engine(Backend backend)
  : mBackend{backend}
{
  if (mBackend == Backend::none)
    throw std::runtime_error{"[ERROR] Invalid backend selected"};
  
  switch (mBackend)
  {
    case Backend::gl_core_43:
      SDL_Log("[INFO] Selected backend: gl_core_43");
      break;
    case Backend::gles2_core_32:
      SDL_Log("[INFO] Selected backend: gles2_core_32");
      break;
    case Backend::none:
      break;
  }
}

Engine::~Engine()
{}

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

