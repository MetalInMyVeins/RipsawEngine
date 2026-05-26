#include "RipsawEngine/3D/Core/Engine.hxx"

#if defined(RIPSAW_ENGINE_TARGET_ANDROID)
#include <SDL3/SDL_main.h>
#endif

#include <cstdlib>
#include <exception>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
  try
  {
    RipsawEngine::_3D::Engine engine{};
    engine.init();
    engine.run();
  }
  catch (const std::exception& e)
  {
    SDL_Log("%s\nAborting\n", e.what());
    std::exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}

