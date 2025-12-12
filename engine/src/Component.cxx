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
  SDL_Log("[INFO] Removed Component: %p from Actor: %p", (void*)this, (void*)mOwner);
}

void Component::update(double dt)
{}

}

