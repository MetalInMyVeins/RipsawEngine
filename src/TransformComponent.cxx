#include "TransformComponent.hxx"
#include "Actor.hxx"

TransformComponent::TransformComponent(Actor* actor, const glm::vec2& pos, const glm::vec2& vel)
  : Component{actor},
    mPos{pos},
    mVel{vel}
{
  mOwner->setTransformComponent(this);
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::update(double dt)
{
  mPos.x += mVel.x * dt;
  mPos.y += mVel.y * dt;
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

