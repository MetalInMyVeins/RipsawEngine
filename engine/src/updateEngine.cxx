#include "RipsawEngine/Core/Engine.hxx"
#include "RipsawEngine/Scene/Actor.hxx"

namespace RipsawEngine
{

void Engine::updateEngine()
{
  while (!(SDL_GetTicksNS() >= mTicksCount + 16000000));
  double dt{static_cast<double>((SDL_GetTicksNS() - mTicksCount) / 1000000000.f)};
  mTicksCount = SDL_GetTicksNS();
  if (dt > 0.05)
    dt = 0.05;
  mtimer += dt;
  ++mFrames;
  if (mtimer >= 1.f)
  {
    SDL_Log("[INFO] Rendering at: %d FPS", mFrames);
    mFrames = 0;
    mtimer = 0;

    for (const auto& actor : mActors)
    {
      SDL_Log("[INFO] Actor: %p", (void*)actor);
      SDL_Log("\tPosition: (%.2f, %.2f)", actor->getPosition().x, actor->getPosition().y);
      SDL_Log("\tVelocity: (%.2f, %.2f)", actor->getVelocity().x, actor->getVelocity().y);
    }
  }

  for (const auto& actor : mActors)
  {
    actor->update(dt);
  }
}

}

