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
  SDL_Log("[INFO] Removed component from Actor: %p", (void*)mOwner);
  SDL_Log("\tAddress: %p", (void*)this);
}

void Component::update(double dt)
{}

}

