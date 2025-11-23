#include "RipsawEngine/Core/Engine.hxx"

namespace RipsawEngine
{

void Engine::processInput()
{
  SDL_Event event;
  SDL_zero(event);

  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_EVENT_QUIT)
    {
      mIsRunning = false;
    }
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
      if (event.key.key == SDLK_ESCAPE)
        mIsRunning = false;
    }
  }
}

}

