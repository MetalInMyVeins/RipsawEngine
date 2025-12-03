#include "RipsawEngine/Core/Core.hxx"
#include "RipsawEngine/Scene/Scene.hxx"

class Sandbox : public RipsawEngine::Game
{
private:
  RipsawEngine::Actor* a1{nullptr};
  RipsawEngine::TransformComponent* tc1{nullptr};
  RipsawEngine::SpriteComponent* sc1{nullptr};
  
  RipsawEngine::Actor* a2{nullptr};
  RipsawEngine::TransformComponent* tc2{nullptr};
  RipsawEngine::SpriteComponent* sc2{nullptr};
  
  RipsawEngine::Actor* a3{nullptr};
  RipsawEngine::TransformComponent* tc3{nullptr};
  RipsawEngine::SpriteComponent* sc3{nullptr};

public:
  void initGame() override
  {
    a1 = new RipsawEngine::Actor{mEngine};
    tc1 = new RipsawEngine::TransformComponent(a1, {1300, 400}, {-250, 0});
    sc1 = new RipsawEngine::SpriteComponent(a1, mEngine->getRenderer(), {30, 30}, {0, 255, 255, 255});
    
    a2 = new RipsawEngine::Actor{mEngine};
    tc2 = new RipsawEngine::TransformComponent(a2, {1300, 300}, {-250, 0});
    sc2 = new RipsawEngine::SpriteComponent(a2, mEngine->getRenderer(), {30, 30}, {255, 0, 0, 255});
    
    a3 = new RipsawEngine::Actor{mEngine};
    tc3 = new RipsawEngine::TransformComponent(a3, {1300, 200}, {-250, 0});
    sc3 = new RipsawEngine::SpriteComponent(a3, mEngine->getRenderer(), {30, 30}, {0, 255, 0, 255});
  }

  void updateGame(double dt) override
  {
    if (a1->getPosition().x <= 700)
    {
      a1->setPosition({1300, 400});
    }
    if (a2->getPosition().x <= 700)
    {
      a2->setPosition({1300, 300});
    }
    if (a3->getPosition().x <= 700)
    {
      a3->setPosition({1300, 200});
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

