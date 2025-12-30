#include <stdexcept>

#include "RipsawEngine/Core/Engine.hxx"
#include "RipsawEngine/Scene/Actor.hxx"
#include "RipsawEngine/Scene/Component.hxx"
#include "RipsawEngine/Scene/TransformComponent.hxx"
#include "RipsawEngine/Scene/SpriteComponent.hxx"

namespace RipsawEngine
{

Actor::Actor(Engine* engine)
  : mEngine{engine}
{
  SDL_Log("[INFO] Actor (%ld bytes) created: %p", sizeof(*this), (void*)this);
  mEngine->addActor(this);
}

Actor::~Actor()
{
  mEngine->removeActorSpritePair(this);
  while (!mComponents.empty())
  {
    delete mComponents.back();
    mComponents.pop_back();
  }
  SDL_Log("[INFO] Actor destroyed: %p", (void*)this);
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

TransformComponent* Actor::getTransformComponent() const
{
  return mTransformComponent;
}

void Actor::setTransformComponent(TransformComponent* tc)
{
  mTransformComponent = tc;
}

void Actor::setSpriteComponent(class SpriteComponent* sc)
{
  mSpriteComponent = sc;
}

SpriteComponent* Actor::getSpriteComponent() const
{
  return mSpriteComponent;
}

glm::vec2 Actor::getPosition() const
{
  if (mTransformComponent == nullptr)
  {
    SDL_Log("[ERROR] TransformComponent unavailable for Actor: %p", (void*)this);
    return {};
  }
  return mTransformComponent->getPosition();
}

void Actor::setPosition(const glm::vec2& pos)
{
  if (mTransformComponent == nullptr)
  {
    SDL_Log("[ERROR] TransformComponent unavailable for Actor: %p", (void*)this);
    return;
  }
  mTransformComponent->setPosition(pos);
}

glm::vec2 Actor::getVelocity() const
{
  if (mTransformComponent == nullptr)
  {
    SDL_Log("[ERROR] TransformComponent unavailable for Actor: %p", (void*)this);
    return {};
  }
  return mTransformComponent->getVelocity();
}

void Actor::setVelocity(const glm::vec2& vel)
{
  if (mTransformComponent == nullptr)
  {
    SDL_Log("[ERROR] TransformComponent unavailable for Actor: %p", (void*)this);
    return;
  }
  mTransformComponent->setVelocity(vel);
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

void Actor::createTransformComponent(const glm::vec2& pos, const glm::vec2& vel)
{
  [[maybe_unused]] Component* tempComponent{new TransformComponent(this, pos, vel)};
}

void Actor::createSpriteComponent(const std::string& imgfile)
{
  Component* tempComponent{new SpriteComponent{this, mEngine->getRenderer(), imgfile}};
  mEngine->insertActorSpritePair(std::make_pair(this, tempComponent));
}

void Actor::createSpriteComponent(const std::pair<float, float>& size, const std::tuple<unsigned char, unsigned char, unsigned char, unsigned char>& color)
{
  Component* tempComponent{new SpriteComponent(this, mEngine->getRenderer(), size, color)};
  mEngine->insertActorSpritePair(std::make_pair(this, tempComponent));
}

}

