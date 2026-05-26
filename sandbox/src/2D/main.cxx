#include "RipsawEngine/2D/Core/Core.hxx"
#include "RipsawEngine/2D/Managers/BGManager.hxx"
#include "RipsawEngine/2D/Scene/Scene.hxx"

#if defined(RIPSAW_ENGINE_TARGET_ANDROID)
#include <SDL3/SDL_main.h>
#endif

class Sandbox : public RipsawEngine::Game
{
public:
  Sandbox() = default;
  ~Sandbox()
  {}

private:
  RipsawEngine::BGManager* bgm{nullptr};
  RipsawEngine::Actor* a1{nullptr};

public:
  void initGame() override
  {
#if defined(RIPSAW_ENGINE_TARGET_LINUX) || defined(RIPSAW_ENGINE_TARGET_WINDOWS)
    std::string asset1{"sandbox/assets/woods.png"};
    std::string asset2{"sandbox/assets/man.png"};
#elif defined(RIPSAW_ENGINE_TARGET_ANDROID)
    std::string asset1{"woods.png"};
    std::string asset2{"man.png"};
#endif
    bgm = mEngine->createBGManager({asset1}, {-55});
    a1 = mEngine->createActor();
    a1->createTransformComponent({300, 650}, {});
    a1->createSpritesheetComponent(asset2, {6, 1}, {1, 1}, true, 5);
  }

  void updateGame([[maybe_unused]] double dt) override
  {
    bgm->update();
  }

  void renderGame() override
  {}
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
  Sandbox sandbox;
  RipsawEngine::Engine engine{&sandbox};
  engine.setRendererBackend("opengl");

  if (engine.init() == false)
  {
    return -1;
  }

  engine.run();
  engine.shutdown();
  return 0;
}

