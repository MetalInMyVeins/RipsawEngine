#include "RipsawEngine/3D/Core/Engine.hxx"

#include <cstdlib>
#include <exception>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
  try
  {
    RipsawEngine::Engine engine{};
    engine.init();
  }
  catch (const std::exception& e)
  {
    SDL_Log("%s", e.what());
    std::exit(EXIT_FAILURE);
  }
  return 0;
}

