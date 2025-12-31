#include <stdexcept>

#include <glm/glm.hpp>

#include "RipsawEngine/Core/Engine.hxx"
#include "RipsawEngine/Managers/BGManager.hxx"
#include "RipsawEngine/Scene/Actor.hxx"
#include "RipsawEngine/Scene/SpriteComponent.hxx"
#include "RipsawEngine/Scene/TransformComponent.hxx"

namespace RipsawEngine
{

BGManager::BGManager(Engine* engine, const std::vector<std::string>& layers, const std::vector<float>& layerSpeeds)
  : mEngine{engine},
    mLayers{layers},
    mLayerSpeeds{layerSpeeds}
{
  if (mLayers.size() != mLayerSpeeds.size())
  {
    throw std::runtime_error{"BGManager::BGManager(): layers should be provided with equal number of speed factors"};
  }
  mActorTriplets.reserve(mLayers.size() * 3);

  for (size_t i{}; i < mLayers.size(); ++i)
  {
    Actor* middle{nullptr};
    Actor* right{nullptr};
    Actor* left{nullptr};

    middle = mEngine->createActor();
    middle->createTransformComponent({0, 0}, {mLayerSpeeds[i], 0});
    middle->createSpriteComponent(mLayers[i]);
    middle->getSpriteComponent()->fitByAspectRatio();
    middle->setPosition({static_cast<float>(mEngine->getScreenSize().first) / 2.f, static_cast<float>(mEngine->getScreenSize().second) / 2.f});

    right = mEngine->createActor();
    right->createTransformComponent({0, 0}, {mLayerSpeeds[i], 0});
    right->createSpriteComponent(mLayers[i]);
    right->getSpriteComponent()->fitByAspectRatio();
    right->setPosition({middle->getPosition().x + middle->getSpriteComponent()->getTexSize().x, static_cast<float>(mEngine->getScreenSize().second) / 2.f});
    
    left = mEngine->createActor();
    left->createTransformComponent({0, 0}, {mLayerSpeeds[i], 0});
    left->createSpriteComponent(mLayers[i]);
    left->getSpriteComponent()->fitByAspectRatio();
    left->setPosition({middle->getPosition().x - middle->getSpriteComponent()->getTexSize().x, static_cast<float>(mEngine->getScreenSize().second) / 2.f});

    mActorTriplets.push_back(std::make_tuple(middle, right, left));
  }
}

void BGManager::update()
{
  for (const auto& triplet : mActorTriplets)
  {
    Actor* middle{std::get<0>(triplet)};
    Actor* right{std::get<1>(triplet)};
    Actor* left{std::get<2>(triplet)};

    if (middle->getPosition().x + middle->getSpriteComponent()->getTexSize().x / 2.f < 0)
    {
      left->setPosition({
        right->getPosition().x + right->getSpriteComponent()->getTexSize().x,
        static_cast<float>(right->getEngine()->getScreenSize().second) / 2.f
      });
    }
    
    if (right->getPosition().x + right->getSpriteComponent()->getTexSize().x / 2.f < 0)
    {
      middle->setPosition({
        left->getPosition().x + left->getSpriteComponent()->getTexSize().x,
        static_cast<float>(left->getEngine()->getScreenSize().second) / 2.f
      });
    }
    
    if (left->getPosition().x + left->getSpriteComponent()->getTexSize().x / 2.f < 0)
    {
      right->setPosition({
        middle->getPosition().x + middle->getSpriteComponent()->getTexSize().x,
        static_cast<float>(middle->getEngine()->getScreenSize().second) / 2.f
      });
    }
    
    if (middle->getPosition().x - middle->getSpriteComponent()->getTexSize().x / 2.f > static_cast<float>(middle->getEngine()->getScreenSize().first))
    {
      right->setPosition({
        left->getPosition().x - left->getSpriteComponent()->getTexSize().x,
        static_cast<float>(left->getEngine()->getScreenSize().second) / 2.f
      });
    }
    
    if (left->getPosition().x - left->getSpriteComponent()->getTexSize().x / 2.f > static_cast<float>(left->getEngine()->getScreenSize().first))
    {
      middle->setPosition({
        right->getPosition().x - right->getSpriteComponent()->getTexSize().x,
        static_cast<float>(right->getEngine()->getScreenSize().second) / 2.f
      });
    }
    
    if (right->getPosition().x - right->getSpriteComponent()->getTexSize().x / 2.f > static_cast<float>(right->getEngine()->getScreenSize().first))
    {
      left->setPosition({
        middle->getPosition().x - middle->getSpriteComponent()->getTexSize().x,
        static_cast<float>(middle->getEngine()->getScreenSize().second) / 2.f
      });
    }
  }
}

void BGManager::setSpeeds(const std::vector<float>& speeds)
{
  if (mLayers.size() != speeds.size())
  {
    throw std::runtime_error{"BGManager::setSpeeds(): layers should be provided with equal number of speed factors"};
  }
  mLayerSpeeds = speeds;
  size_t i{};

  for (const auto& triplet : mActorTriplets)
  {
    std::get<0>(triplet)->getTransformComponent()->setVelocity({mLayerSpeeds[i], 0});
    std::get<1>(triplet)->getTransformComponent()->setVelocity({mLayerSpeeds[i], 0});
    std::get<2>(triplet)->getTransformComponent()->setVelocity({mLayerSpeeds[i], 0});
    ++i;
  }
}
  
void BGManager::changeSpeedBy(float dx, float dy)
{
  for (const auto& triplet : mActorTriplets)
  {
    glm::vec2 currentVel{std::get<0>(triplet)->getTransformComponent()->getVelocity()};
    
    std::get<0>(triplet)->getTransformComponent()->setVelocity({currentVel.x + dx, currentVel.y + dy});
    std::get<1>(triplet)->getTransformComponent()->setVelocity({currentVel.x + dx, currentVel.y + dy});
    std::get<2>(triplet)->getTransformComponent()->setVelocity({currentVel.x + dx, currentVel.y + dy});
  }
}

}

