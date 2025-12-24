#include "RipsawEngine/Core/Core.hxx"
#include "RipsawEngine/Managers/BGManager.hxx"
#include "RipsawEngine/Scene/Scene.hxx"

class Sandbox : public RipsawEngine::Game
{
public:
  Sandbox() = default;
  ~Sandbox()
  {
    delete bgm;
  }

private:
  RipsawEngine::BGManager* bgm{nullptr};
  RipsawEngine::Actor* a1{nullptr};

public:
  void initGame() override
  {
    bgm = new RipsawEngine::BGManager{mEngine, {"sandbox/assets/bglayer1.png", "sandbox/assets/bglayer2.png"}, {-40, -110}};
    a1 = mEngine->createActor();
    a1->createTransformComponent({300, 300}, {});
    a1->createSpriteComponent("sandbox/assets/7.png");
  }

  void updateGame(double dt) override
  {
    bgm->update();
  }

  void renderGame() override
  {}
};

int main(int argv, char** argc)
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

