#include "Component.hxx"
#include "Actor.hxx"

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

