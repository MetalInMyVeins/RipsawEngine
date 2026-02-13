#include <stdexcept>

#include "RipsawEngine/Scene/Actor.hxx"
#include "RipsawEngine/Scene/TransformComponent.hxx"

namespace RipsawEngine
{

TransformComponent::TransformComponent(Actor* actor, const glm::vec2& pos, const glm::vec2& vel)
  : Component{actor},
    mPos{pos},
    mVel{vel}
{
  mOwner->helperRegisterComponent("TransformComponent");

  mOwner->setTransformComponent(this);

  if (this->isComponentValid())
  {
    SDL_Log("[INFO] Component added: TransformComponent: %p to Actor: %p", static_cast<void*>(this), static_cast<void*>(mOwner));
  }
  else
  {
    SDL_Log("[ERROR] TransformComponent construction FAILED");
  }
}

TransformComponent::~TransformComponent()
{
  mOwner->deregisterComponent("TransformComponent");
}

bool TransformComponent::isComponentValid() const
{
  return true;
}

void TransformComponent::update(double dt)
{
  mPos.x += mVel.x * static_cast<float>(dt);
  mPos.y += mVel.y * static_cast<float>(dt);
}

glm::vec2 TransformComponent::getPosition() const
{
  return mPos;
}

void TransformComponent::setPosition(const glm::vec2& pos)
{
  mPos = pos;
}

glm::vec2 TransformComponent::getVelocity() const
{
  return mVel;
}

void TransformComponent::setVelocity(const glm::vec2& vel)
{
  mVel = vel;
}

}

