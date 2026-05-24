#include "RipsawEngine/3D/Core/Engine.hxx"

#include <cstdlib>
#include <exception>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
  try
  {
    RipsawEngine::_3D::Engine engine{RipsawEngine::_3D::Backend::gl_core_43};
    engine.init();
    engine.run();
  }
  catch (const std::exception& e)
  {
    SDL_Log("%s\nAborting\n", e.what());
    std::exit(EXIT_FAILURE);
  }
  return 0;
}

