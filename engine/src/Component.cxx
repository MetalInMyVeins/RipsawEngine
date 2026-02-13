#include "RipsawEngine/Scene/Actor.hxx"
#include "RipsawEngine/Scene/Component.hxx"

namespace RipsawEngine
{

Component::Component(Actor* actor)
  : mOwner{actor}
{
  mOwner->addComponent(this);
}

Component::~Component()
{
  SDL_Log("[INFO] Removed Component: %p from Actor: %p", static_cast<void*>(this), static_cast<void*>(mOwner));
}

void Component::update([[maybe_unused]] double dt)
{}

}

