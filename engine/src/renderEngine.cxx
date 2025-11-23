#include "RipsawEngine/Core/Engine.hxx"

namespace RipsawEngine
{

void Engine::renderEngine()
{
  SDL_SetRenderDrawColor(mRenderer, 40, 40, 40, 255);
  SDL_RenderClear(mRenderer);
  SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
  SDL_RenderPresent(mRenderer);
}

}

