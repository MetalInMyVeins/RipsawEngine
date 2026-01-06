#include "RipsawEngine/Core/Engine.hxx"
#include "RipsawEngine/Scene/Actor.hxx"

namespace RipsawEngine
{

void Engine::updateEngine()
{
  // Frame locking code would go here.
  // But the preferred philosophy is to let the loop
  // run as fast as possible depending on the hardware.

  // Delta-time calculation goes here.
  Uint64 now{SDL_GetTicksNS()};
  double dt{ static_cast<double>(now - mTicksCount) / 1'000'000'000.0 };
  mDt = dt;
  mTicksCount = now;

  if (dt > 0.05)
    dt = 0.05;
  
  mtimer += dt;
  ++mFrames;
  
  if (mtimer >= 1.f)
  {
    SDL_Log("[INFO] Rendering at: %d FPS", mFrames);
    mFrames = 0;
    mtimer = 0;

    for ([[maybe_unused]] const auto& actor : mActors)
    {
      // SDL_Log("[INFO] Actor: %p", (void*)actor);
      // SDL_Log("\tPosition: (%.2f, %.2f)", actor->getPosition().x, actor->getPosition().y);
      // SDL_Log("\tVelocity: (%.2f, %.2f)", actor->getVelocity().x, actor->getVelocity().y);
    }
  }

  for (auto& actor : mActorsToBeKilled)
  {
    this->destroyActor(actor);
  }
  mActorsToBeKilled.clear();

  mActorsBeingUpdated = true;
  for (const auto& actor : mActors)
  {
    actor->update(dt);
  }
  mActorsBeingUpdated = false;
}

}

