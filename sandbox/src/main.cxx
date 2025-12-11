#include "RipsawEngine/Core/Core.hxx"
#include "RipsawEngine/Scene/Scene.hxx"

class Sandbox : public RipsawEngine::Game
{
public:
  Sandbox() = default;
  ~Sandbox()
  {}

private:
  RipsawEngine::Actor* a1{nullptr};
  RipsawEngine::Actor* a2{nullptr};
  RipsawEngine::Actor* a3{nullptr};

public:
  void initGame() override
  {
    a1 = mEngine->createActor();
    a1->createTransformComponent({1300, 300}, {-200, 0});
    a1->createSpriteComponent({30, 30}, {255, 0, 0, 255});
    
    a2 = mEngine->createActor();
    a2->createTransformComponent({1300, 400}, {-100, 0});
    a2->createSpriteComponent({30, 30}, {255, 255, 0, 255});
    
    a3 = mEngine->createActor();
    a3->createTransformComponent({1300, 500}, {-150, 0});
    a3->createSpriteComponent({30, 30}, {255, 0, 255, 255});
  }

  void updateGame(double dt) override
  {
    if (a1)
    {
      if (a1->getPosition().x <= 700)
      {
        a1->setPosition({1300, 300});
        mEngine->destroyActor(a1);
      }
    }
    if (a2)
    {
      if (a2->getPosition().x <= 700)
      {
        a2->setPosition({1300, 400});
      }
    }
    if (a3)
    {
      if (a3->getPosition().x <= 700)
      {
        a3->setPosition({1300, 500});
      }
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

