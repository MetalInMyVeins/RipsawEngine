#include "RipsawEngine/3D/Core/Engine.hxx"

#include <glad/glad.h>

#include <stdexcept>
#include <string>

namespace RipsawEngine::_3D
{

Engine::Engine(Backend backend)
  : mBackend{backend}
{
  SDL_Log("[START] RipsawEngine::_3D subsystem");

  if (mBackend == Backend::none)
    throw std::runtime_error{"[ERROR] Invalid backend selected"};
  
  switch (mBackend)
  {
    case Backend::gl_core_43:
      SDL_Log("[INFO] Selected backend: gl_core_43");
      break;
    case Backend::gles2_core_32:
      SDL_Log("[INFO] Selected backend: gles2_core_32");
      break;
    case Backend::none:
      break;
  }
}

Engine::~Engine()
{
  SDL_GL_DestroyContext(mContext);
  SDL_Log("[INFO] Destroyed OpenGL context");
  SDL_DestroyWindow(mWindow);
  SDL_Log("[INFO] Destroyed window");
  SDL_Log("[STOP] RipsawEngine::_3D subsystem");
}

void Engine::init()
{
  bool status = SDL_Init(SDL_INIT_VIDEO);
  if (status == false)
    throw std::runtime_error{"[ERROR] SDL3 initialization failure"};

  SDL_DisplayID did = SDL_GetPrimaryDisplay();
  const SDL_DisplayMode* dm = SDL_GetCurrentDisplayMode(did);
  mWidth = dm->w;
  mHeight = dm->h;
  if (mWidth <= 0 or mHeight <= 0)
    throw std::runtime_error{"[ERROR] Invalid display dimension"};
  SDL_Log("[INFO] Detected display dimension: %d X %d", mWidth, mHeight);
}

void Engine::initGL()
{
  if (mBackend == Backend::gl_core_43)
  {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  }
  else if (mBackend == Backend::gles2_core_32)
  {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  }
  SDL_Log("[INFO] GL attributes set up");

  mWindow = SDL_CreateWindow("RipsawEngine3D", mWidth, mHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
  if (mWindow == nullptr)
    throw std::runtime_error{"[ERROR] %s" + std::string{SDL_GetError()}};
  SDL_Log("[INFO] Created window: %d X %d", mWidth, mHeight);

  if (mBackend == Backend::gl_core_43)
  {
#ifdef RIPSAW_GL
    mContext = SDL_GL_CreateContext(mWindow);
    SDL_Log("[INFO] Created OpenGL context");
    int gladinit = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress));
    if (gladinit == 0)
      throw std::runtime_error{"[ERROR] GLAD init failed"};
    SDL_Log("[INFO] GLAD initialized");
    SDL_Log("\tGL Vendor:\t%s", glGetString(GL_VENDOR));
    SDL_Log("\tGL Renderer:\t%s", glGetString(GL_RENDERER));
    SDL_Log("\tGL Version:\t%s", glGetString(GL_VERSION));
    SDL_Log("\tGLSL Version:\t%s", glGetString(GL_SHADING_LANGUAGE_VERSION));
  }
#elifdef RIPSAW_GLES2
  else if (mBackend == Backend::gles2_core_32)
  {
    mContext = SDL_GL_CreateContext(mWindow);
    SDL_Log("[INFO] Created OpenGL context");
    int gladinit = gladLoadGLES2Loader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress));
    if (gladinit == 0)
      throw std::runtime_error{"[ERROR] GLAD init failed"};
    SDL_Log("[INFO] GLAD initialized");
    SDL_Log("\tGL Vendor:\t%s", glGetString(GL_VENDOR));
    SDL_Log("\tGL Renderer:\t%s", glGetString(GL_RENDERER));
    SDL_Log("\tGL Version:\t%s", glGetString(GL_VERSION));
    SDL_Log("\tGLSL Version:\t%s", glGetString(GL_SHADING_LANGUAGE_VERSION));
  }
#endif
  glViewport(0, 0, mWidth, mHeight);
  SDL_Log("[INFO] Viewport created: %d X %d", mWidth, mHeight);

  while (mRunning)
  {
    SDL_Event event{};
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT)
        mRunning = false;
      if (event.key.key == SDLK_ESCAPE)
        mRunning = false;
    }

    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(mWindow);
  }
}

}

