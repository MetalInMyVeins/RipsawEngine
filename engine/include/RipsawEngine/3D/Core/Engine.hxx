#ifndef D3_CORE_ENGINE_HXX
#define D3_CORE_ENGINE_HXX

#include <SDL3/SDL.h>

namespace RipsawEngine
{

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

