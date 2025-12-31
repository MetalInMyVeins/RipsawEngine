#include "RipsawEngine/Core/Engine.hxx"
#include "RipsawEngine/Scene/Scene.hxx"

namespace RipsawEngine
{

void Engine::renderEngine()
{
  SDL_SetRenderDrawColor(mRenderer, 40, 40, 40, 255);
  SDL_RenderClear(mRenderer);

  for (const auto& sprite : mSprites)
  {
    sprite->draw(mDt);
  }

  SDL_RenderPresent(mRenderer);
}

}

