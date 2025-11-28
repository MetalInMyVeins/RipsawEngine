#include "RipsawEngine/Core/Core.hxx"
#include "RipsawEngine/Scene/Scene.hxx"

class Sandbox : public RipsawEngine::Game
{
private:
  RipsawEngine::Actor* a1{nullptr};
  RipsawEngine::TransformComponent* tc1{nullptr};
  RipsawEngine::SpriteComponent* sc1{nullptr};

public:
  void initGame() override
  {
    a1 = new RipsawEngine::Actor{mEngine};
    tc1 = new RipsawEngine::TransformComponent(a1, {1300, 400}, {-250, 0});
    sc1 = new RipsawEngine::SpriteComponent(a1, mEngine->getRenderer(), {30, 30}, {0, 255, 255, 255});
  }

  void updateGame(double dt) override
  {
    if (a1->getPosition().x <= 700)
    {
      a1->setPosition({1300, 400});
    }
  }

  void renderGame() override
  {}
};

int main(int argv, char** argc)
{
  Sandbox sandbox;
  RipsawEngine::Engine engine{&sandbox};

  if (engine.init() == false)
  {
    return -1;
  }

  engine.run();
  engine.shutdown();
  return 0;
}

