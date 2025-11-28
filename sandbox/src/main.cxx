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
  RipsawEngine::TransformComponent* tc{new RipsawEngine::TransformComponent(actor, {engine.getScreenSize().first / 2.f, engine.getScreenSize().second / 2.f}, {130, 30})};
  RipsawEngine::SpriteComponent* sc{new RipsawEngine::SpriteComponent(actor, engine.getRenderer(), {40, 40}, {255, 0, 0, 255})};

  RipsawEngine::Actor* actor2{new RipsawEngine::Actor{&engine}};
  RipsawEngine::TransformComponent* tc2{new RipsawEngine::TransformComponent(actor2, {engine.getScreenSize().first / 2.f, engine.getScreenSize().second / 2.f}, {-130, -30})};
  RipsawEngine::SpriteComponent* sc2{new RipsawEngine::SpriteComponent(actor2, engine.getRenderer(), {40, 40}, {255, 0, 255, 255})};

  engine.run();
  engine.shutdown();
  return 0;
}

