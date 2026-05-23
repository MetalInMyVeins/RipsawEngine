#ifndef D3_CORE_ENGINE_HXX
#define D3_CORE_ENGINE_HXX

#include <SDL3/SDL.h>

namespace RipsawEngine::_3D
{

enum class Backend
{
  none,
  gl_core_43,
  gles2_core_32,
};

class Engine
{
public:
  Engine(Backend backend);
  ~Engine();
  void init();

private:
  Backend mBackend{Backend::none};
  int mWidth{};
  int mHeight{};
};

}

#endif

