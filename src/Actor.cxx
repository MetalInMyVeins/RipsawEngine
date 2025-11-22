#include "Actor.hxx"
#include "Engine.hxx"
#include "Component.hxx"
#include "TransformComponent.hxx"

Actor::Actor(Engine* engine)
  : mEngine{engine}
{
  mEngine->addActor(this);
  SDL_Log("[INFO] Actor created");
  SDL_Log("\tAddress: %p", (void*)this);
  SDL_Log("\tSize: %ld bytes", sizeof(*this));
}

Actor::~Actor()
{
  for (const auto& component : mComponents)
  {
    if (component != nullptr)
      delete component;
  }
  if (mTransformComponent != nullptr)
    mTransformComponent = nullptr;

  mEngine->removeActor(this);
  SDL_Log("[INFO] Actor destroyed");
  SDL_Log("\tAddress: %p", (void*)this);
}

void Actor::update(double dt)
{
  this->updateComponents(dt);
}

void Actor::updateComponents(double dt)
{
  for (const auto& comp : mComponents)
  {
    comp->update(dt);
  }
}

void Actor::addComponent(Component* component)
{
  mComponents.emplace_back(component);
}

void Actor::removeComponent(Component* component)
{
}

TransformComponent* Actor::getTransformComponent() const
{
  return mTransformComponent;
}

void Actor::setTransformComponent(TransformComponent* tc)
{
  mTransformComponent = tc;
}

glm::vec2 Actor::getPosition() const
{
  if (mTransformComponent == nullptr)
  {
    SDL_Log("[ERROR] TransformComponent not available for Actor: %p", (void*)this);
    return {};
  }
  return mTransformComponent->getPosition();
}

void Actor::setPosition(const glm::vec2& pos)
{
  if (mTransformComponent == nullptr)
  {
    SDL_Log("[ERROR] TransformComponent not available for Actor: %p", (void*)this);
    return;
  }
  mTransformComponent->setPosition(pos);
}

glm::vec2 Actor::getVelocity() const
{
  if (mTransformComponent == nullptr)
  {
    SDL_Log("[ERROR] TransformComponent not available for Actor: %p", (void*)this);
    return {};
  }
  return mTransformComponent->getVelocity();
}

void Actor::setVelocity(const glm::vec2& vel)
{
  if (mTransformComponent == nullptr)
  {
    SDL_Log("[ERROR] TransformComponent not available for Actor: %p", (void*)this);
    return;
  }
  mTransformComponent->setPosition(vel);
}

