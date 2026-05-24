#ifndef _3D_CORE_ENGINE_HXX
#define _3D_CORE_ENGINE_HXX

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
  void initGL();
  void run();

private:
  Backend mBackend{Backend::none};
  int mWidth{};
  int mHeight{};
  SDL_Window* mWindow{nullptr};
  SDL_GLContext mContext{};
  bool mRunning{true};
};

}

#endif

