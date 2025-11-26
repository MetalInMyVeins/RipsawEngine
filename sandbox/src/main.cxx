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
  RipsawEngine::TransformComponent* tc{new RipsawEngine::TransformComponent(actor, {engine.getScreenSize().first / 2.f, engine.getScreenSize().second / 2.f}, {80, 30})};
  RipsawEngine::SpriteComponent* sc{new RipsawEngine::SpriteComponent(actor, engine.getRenderer(), {40, 40}, {255, 0, 0, 255})};

  engine.run();
  engine.shutdown();
  return 0;
}

