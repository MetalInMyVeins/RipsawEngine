#include <stdexcept>

#include "RipsawEngine/Core/Engine.hxx"
#include "RipsawEngine/Scene/Actor.hxx"
#include "RipsawEngine/Scene/Component.hxx"
#include "RipsawEngine/Scene/TransformComponent.hxx"

namespace RipsawEngine
{

Actor::Actor(Engine* engine)
  : mEngine{engine}
{
  SDL_Log("[INFO] Actor created: %p", (void*)this);
  SDL_Log("\tSize: %ld bytes", sizeof(*this));
  mEngine->addActor(this);
}

Actor::~Actor()
{
  for (const auto& component : mComponents)
  {
    if (component != nullptr)
    {
      delete component;
    }
  }
  if (mTransformComponent != nullptr)
  {
    mTransformComponent = nullptr;
  }

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
  mTotalComponentSize += sizeof(*component);
  SDL_Log("[INFO] Cumulative component size of Actor %p: %ld bytes", (void*)this, mTotalComponentSize);
}

void Actor::removeComponent(Component* component)
{
  auto it{std::find(mComponents.begin(), mComponents.end(), component)};
  if (it != mComponents.end())
  {
    mComponents.erase(it);
  }
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

Engine* Actor::getEngine() const
{
  return mEngine;
}

bool Actor::hasComponent(const std::string& compname) const
{
  if (mComponentMap.contains(compname))
  {
    return mComponentMap.at(compname);
  }
  return false;
}

void Actor::registerComponent(const std::string& compname)
{
  mComponentMap[compname] = true;
}

void Actor::deregisterComponent(const std::string& compname)
{
  mComponentMap[compname] = false;
}
  
void Actor::helperRegisterComponent(const std::string& compname)
{
  if (this->hasComponent(compname))
  {
    throw std::runtime_error{"[ABORT] Actor already owns " + compname};
  }
  this->registerComponent(compname);
}

}

