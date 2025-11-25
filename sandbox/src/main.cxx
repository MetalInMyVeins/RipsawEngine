#include "RipsawEngine/Core/Core.hxx"
#include "RipsawEngine/Scene/Scene.hxx"

int main(int argv, char** argc)
{
  RipsawEngine::Engine engine;
  if (engine.init() == false)
  {
    return -1;
  }

  // Engine testing code goes here.
  RipsawEngine::Actor* actor{new RipsawEngine::Actor{&engine}};
  RipsawEngine::TransformComponent* tc{new RipsawEngine::TransformComponent(actor, {engine.getScreenSize().first / 2.f, engine.getScreenSize().second / 2.f}, {0, 0})};
  RipsawEngine::SpriteComponent* sc{new RipsawEngine::SpriteComponent(actor, engine.getRenderer(), "sandbox/assets/back1.png")};

  engine.run();
  engine.shutdown();
  return 0;
}

