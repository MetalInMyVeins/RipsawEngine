#include "RipsawEngine/2D/Core/Core.hxx"
#include "RipsawEngine/2D/Managers/BGManager.hxx"
#include "RipsawEngine/2D/Scene/Scene.hxx"

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
    bgm = mEngine->createBGManager({"sandbox/assets/woods.png"}, {-55});
    a1 = mEngine->createActor();
    a1->createTransformComponent({300, 650}, {});
    a1->createSpritesheetComponent("sandbox/assets/man.png", {6, 1}, {1, 1}, true, 5);
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

