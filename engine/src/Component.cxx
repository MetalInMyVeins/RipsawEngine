#include "RipsawEngine/Scene/Component.hxx"
#include "RipsawEngine/Scene/Actor.hxx"

namespace RipsawEngine
{

Component::Component(Actor* actor)
  : mOwner{actor}
{
  mOwner->addComponent(this);
}

Component::~Component()
{
  mOwner->removeComponent(this);
}

void Component::update(double dt)
{}

}

