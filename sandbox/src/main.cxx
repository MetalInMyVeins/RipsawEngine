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
  RipsawEngine::Actor* a2{nullptr};

public:
  void initGame() override
  {
    bgm = new RipsawEngine::BGManager{mEngine, {"sandbox/assets/bglayer1.png", "sandbox/assets/bglayer2.png"}, {-40, -110}};
    a1 = mEngine->createActor();
    a1->createTransformComponent({600, 350}, {});
    a1->createSpriteComponent("sandbox/assets/7.png");
    a1->getSpriteComponent()->rotateClockwiseAmount(90);
    
    a2 = mEngine->createActor();
    a2->createTransformComponent({450, 350}, {});
    a2->createSpriteComponent("sandbox/assets/20.png");
    a2->getSpriteComponent()->rotateClockwiseAmount(90);
    a2->setVelocity({150, 0});
  }

  void updateGame(double dt) override
  {
    bgm->update();
    if (a2->getPosition().x > 750.f)
    {
      a2->getSpriteComponent()->rotateClockwiseAmount(180);
      a2->setVelocity({-150, 0});
      mEngine->actorGoesBelow(a2, a1);
    }
    if (a2->getPosition().x < 450.f)
    {
      a2->getSpriteComponent()->rotateAntiClockwiseAmount(180);
      a2->setVelocity({150, 0});
      mEngine->actorGoesAbove(a2, a1);
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

