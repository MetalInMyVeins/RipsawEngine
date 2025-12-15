#include <stdexcept>

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
  mActorPairs.reserve(mLayers.size() * 2);

  for (size_t i{}; i < mLayers.size(); ++i)
  {
    std::pair<Actor*, Actor*> apair{};

    apair.first = mEngine->createActor();
    apair.first->createTransformComponent({0, 0}, {mLayerSpeeds[i], 0});
    apair.first->createSpriteComponent(mLayers[i]);
    apair.first->getSpriteComponent()->fitByAspectRatio();
    apair.first->setPosition({mEngine->getScreenSize().first / 2.f, mEngine->getScreenSize().second / 2.f});
    
    apair.second = mEngine->createActor();
    apair.second->createTransformComponent({0, 0}, {mLayerSpeeds[i], 0});
    apair.second->createSpriteComponent(mLayers[i]);
    apair.second->getSpriteComponent()->fitByAspectRatio();
    apair.second->setPosition({apair.first->getPosition().x + apair.first->getSpriteComponent()->getTexSize().first, mEngine->getScreenSize().second / 2.f});

    mActorPairs.push_back(apair);
  }
}

void BGManager::update()
{
  for (auto& apair : mActorPairs)
  {
    if (apair.first->getPosition().x + apair.first->getSpriteComponent()->getTexSize().first / 2.f < 0)
    {
      apair.first->setPosition({apair.second->getPosition().x + apair.first->getSpriteComponent()->getTexSize().first, mEngine->getScreenSize().second / 2.f});
    }
    if (apair.second->getPosition().x + apair.first->getSpriteComponent()->getTexSize().first / 2.f < 0)
    {
      apair.second->setPosition({apair.first->getPosition().x + apair.first->getSpriteComponent()->getTexSize().first, mEngine->getScreenSize().second / 2.f});
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
  int i{};

  for (const auto& apair : mActorPairs)
  {
    apair.first->getTransformComponent()->setVelocity({mLayerSpeeds[i], 0});
    apair.second->getTransformComponent()->setVelocity({mLayerSpeeds[i], 0});
    ++i;
  }
}

}

