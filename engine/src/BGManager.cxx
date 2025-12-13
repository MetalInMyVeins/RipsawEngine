#include <stdexcept>

#include "RipsawEngine/Core/Engine.hxx"
#include "RipsawEngine/Managers/BGManager.hxx"
#include "RipsawEngine/Scene/Actor.hxx"
#include "RipsawEngine/Scene/SpriteComponent.hxx"
#include "RipsawEngine/Scene/TransformComponent.hxx"

namespace RipsawEngine
{

BGManager::BGManager(Engine* engine, const std::vector<std::string>& layers, const std::vector<glm::vec2>& layerSpeeds)
  : mEngine{engine},
    mLayers{layers},
    mLayerSpeeds{layerSpeeds}
{
  if (mLayers.size() != mLayerSpeeds.size())
  {
    throw std::runtime_error{"BGManager::BGManager: layers should be provided with equal number of speed factors"};
  }
  mActorPairs.reserve(mLayers.size() * 2);

  for (size_t i{}; i < mLayers.size(); ++i)
  {
    std::pair<Actor*, Actor*> apair{};

    apair.first = mEngine->createActor();
    apair.first->createTransformComponent({0, 0}, mLayerSpeeds[i]);
    apair.first->createSpriteComponent(mLayers[i]);
    apair.first->getSpriteComponent()->fitByAspectRatio();
    apair.first->setPosition({mEngine->getScreenSize().first / 2.f, mEngine->getScreenSize().second / 2.f});
    
    apair.second = mEngine->createActor();
    apair.second->createTransformComponent({0, 0}, mLayerSpeeds[i]);
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
      apair.first->setPosition({apair.second->getPosition().x + apair.first->getSpriteComponent()->getTexSize().first, 384});
    }
    if (apair.second->getPosition().x + apair.first->getSpriteComponent()->getTexSize().first / 2.f < 0)
    {
      apair.second->setPosition({apair.first->getPosition().x + apair.first->getSpriteComponent()->getTexSize().first, 384});
    }
  }
}

}

