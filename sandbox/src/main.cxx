#include "RipsawEngine/Core/Core.hxx"
#include "RipsawEngine/Managers/BGManager.hxx"
#include "RipsawEngine/Scene/Scene.hxx"

class Sandbox : public RipsawEngine::Game
{
public:
  Sandbox() = default;
  ~Sandbox()
  {}

private:
  RipsawEngine::BGManager* bgm{nullptr};
  RipsawEngine::Actor* a1{nullptr};
  RipsawEngine::Actor* a2{nullptr};

public:
  void initGame() override
  {
    bgm = mEngine->createBGManager({"sandbox/assets/bglayer1.png", "sandbox/assets/bglayer2.png"}, {-240, -310});
    a1 = mEngine->createActor();
    a1->createTransformComponent({600, 350}, {});
    a1->createSpritesheetComponent("sandbox/assets/ships2.png", {4, 5}, {3, 2});
    a1->getSpriteComponent()->rotateClockwiseAmount(90);
    a1->getSpriteComponent()->setRotationSpeed(100);
    
    a2 = mEngine->createActor();
    a2->createTransformComponent({450, 350}, {});
    a2->createSpritesheetComponent("sandbox/assets/ships1.png", {4, 2}, {1, 1});
    a2->setVelocity({150, 0});
  }

  void updateGame(double dt) override
  {
    bgm->update();
    if (a2->getPosition().x > 750.f)
    {
      a2->setVelocity({-150, 0});
      a2->getSpriteComponent()->changeCoord({1, 2});
      mEngine->actorGoesBelow(a2, a1);
      bgm->changeSpeedBy(-100);
    }
    if (a2->getPosition().x < 450.f)
    {
      a2->setVelocity({150, 0});
      a2->getSpriteComponent()->changeCoord({1, 1});
      mEngine->actorGoesAbove(a2, a1);
      bgm->changeSpeedBy(100);
    }
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

