#include "RipsawEngine/3D/Core/Engine.hxx"

#include <stdexcept>

namespace RipsawEngine
{

void Engine::init()
{
  bool status = SDL_Init(SDL_INIT_VIDEO);
  if (status == false)
    throw std::runtime_error{"[ERROR] SDL3 initialization failure\n"};
}

}

