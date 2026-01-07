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
  // Get the current time since library initialization, in nanosec.
  Uint64 now{SDL_GetTicksNS()};
  // How many seconds have passed since last frame? That's dt.
  // mTicksCount is the current time of previous frame.
  double dt{static_cast<double>(now - mTicksCount) / 1000000000};
  // Set dt for engine's use.
  mDt = dt;
  mTicksCount = now;

  // Clamp dt to not grow beyond clamp time.
  if (dt > mDtClamp)
    dt = mDtClamp;

  // Accumulate dt and frames to check later.
  mFrameTime += dt;
  ++mFrames;

  // If dt accumulation becomes 1 second, print number of passed frames and reset both to 0.
  if (mFrameTime >= 1.0)
  {
    SDL_Log("[INFO] Rendering at: %d FPS", mFrames);
    mFrameTime = 0;
    mFrames = 0;

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
    // All actor update occurs as a function of dt.
    actor->update(dt);
  }
  mActorsBeingUpdated = false;
}

}

