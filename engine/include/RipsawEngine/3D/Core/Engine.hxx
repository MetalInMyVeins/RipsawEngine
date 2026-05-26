#ifndef _3D_CORE_ENGINE_HXX
#define _3D_CORE_ENGINE_HXX

#include <glad/glad.h>

#include <SDL3/SDL.h>

#include <string>

namespace RipsawEngine::_3D
{

class Engine
{
public:
  Engine();
  ~Engine();
  void init();
  void initDisplay();
  void initGL();
  void initGeom();
  void initShaders();
  void run();

private:
  std::string readFile(const std::string& file);

private:
  int mWidth{};
  int mHeight{};
  SDL_Window* mWindow{nullptr};
  SDL_GLContext mContext{};
  bool mRunning{true};
  GLuint mVao{};
  GLuint mVbo{};
  GLuint mEbo{};
  GLuint mVertexShader{};
  GLuint mFragmentShader{};
  int mCompStat{};
  char mInfolog[512]{};
  GLuint mProgram{};
};

}

#endif

