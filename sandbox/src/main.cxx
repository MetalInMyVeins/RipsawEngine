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

public:
  void initGame() override
  {
    bgm = new RipsawEngine::BGManager{mEngine, {"sandbox/assets/bglayer1.png", "sandbox/assets/bglayer2.png"}, {80, 220}};
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

