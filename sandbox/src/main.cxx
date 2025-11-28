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
  RipsawEngine::TransformComponent* tc{new RipsawEngine::TransformComponent(actor, {300, 300}, {-100, 0})};
  RipsawEngine::SpriteComponent* sc{new RipsawEngine::SpriteComponent(actor, engine.getRenderer(), {30, 30}, {255, 0, 0, 255})};
  
  RipsawEngine::Actor* actor2{new RipsawEngine::Actor{&engine}};
  RipsawEngine::TransformComponent* tc2{new RipsawEngine::TransformComponent(actor2, {1000, 300}, {-100, 0})};
  RipsawEngine::SpriteComponent* sc2{new RipsawEngine::SpriteComponent(actor2, engine.getRenderer(), {30, 30}, {0, 0, 255, 255})};

  engine.run();
  engine.shutdown();
  return 0;
}

