#ifndef D3_CORE_ENGINE_HXX
#define D3_CORE_ENGINE_HXX

#include <SDL3/SDL.h>

namespace RipsawEngine
{

enum class Backend
{
  gl_core_43,
  gles2_core_32,
};

class Engine
{
public:
  void init();

private:
  int mWidth{};
  int mHeight{};
};

}

#endif

