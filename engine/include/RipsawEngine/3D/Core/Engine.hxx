#ifndef _3D_CORE_ENGINE_HXX
#define _3D_CORE_ENGINE_HXX

#include <glad/glad.h>

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
  void initDisplay();
  void initGL();
  void initGeom();
  void initShaders();
  void run();

private:
  Backend mBackend{Backend::none};
  int mWidth{};
  int mHeight{};
  SDL_Window* mWindow{nullptr};
  SDL_GLContext mContext{};
  bool mRunning{true};

private:
  GLuint mVao{};
  GLuint mVbo{};
  GLuint mVertexShader{};
  GLuint mFragmentShader{};
  int mCompStat{};
  char mInfolog[512]{};
  GLuint mProgram{};
};

}

#endif

