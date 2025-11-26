#pragma once

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL3/SDL_log.h>

#include <glm/glm.hpp>

namespace RipsawEngine
{

class Actor
{
public:
  /// Constructs actor with pointer to @ref Engine instance.
  /// @param engine Pointer to @ref Engine instance.
  Actor(class Engine* engine);
  /// Destructs actor.
  virtual ~Actor();
  /// Updates actor.
  /// @param dt Delta-time.
  void update(double dt);
  /// Updates all components tied to the actor.
  /// @param dt Delta-time.
  void updateComponents(double dt);
  /// Adds component to actor storing in @ref mComponents.
  /// @param component Component to be added to actor.
  void addComponent(class Component* component);
  /// Removes component from actor.
  /// @param component Component to be removed from actor.
  void removeComponent(class Component* component);
  /// Returns @ref mTransformComponent.
  /// @details This method works as a way for other components to get access to @ref TransformComponent.
  class TransformComponent* getTransformComponent() const;
  /// Sets @ref mTransformComponent.
  /// @param tc Transform component.
  void setTransformComponent(class TransformComponent* tc);
  /// Returns position of actor.
  glm::vec2 getPosition() const;
  /// Sets position of actor.
  /// @param pos Position of actor.
  void setPosition(const glm::vec2& pos);
  /// Sets velocity of actor.
  glm::vec2 getVelocity() const;
  /// Sets velocity of actor.
  /// @param vel Velocity of actor.
  void setVelocity(const glm::vec2& vel);
  /// Returns mEngine so that other componets can use it if needed.
  class Engine* getEngine() const;
  /// Returns True if the specified component exists in mComponentMap.
  /// @param compname Component name.
  bool hasComponent(const std::string& compname) const;
  /// Registers specified component in mComponentMap.
  /// @param compname Component name.
  void registerComponent(const std::string& compname);
  /// Deregisters component from mComponentMap.
  /// @param compname Component name.
  void deregisterComponent(const std::string& compname);
  /// Helper method to ease out component registration avoiding code duplication.
  /// @warn Throws runtime error if specified component has already been injected in actor.
  /// @param compname Component name.
  void helperRegisterComponent(const std::string& compname);

private:
  /// Main engine instance.
  class Engine* mEngine{nullptr};
  /// Vector of all components tied to the actor.
  std::vector<class Component*> mComponents{};
  /// @ref TransformComponent tied to the actor (if any).
  class TransformComponent* mTransformComponent{nullptr};
  /// Total size of all components held by actor.
  size_t mTotalComponentSize{};
  /// Map of all possible components that actor can hold and their inclusion status in the actor.
  /// @details Components are capabilities of an actor. The philosophy as of now is, no actor should be able to hold the same type of component more than once. To ensure that, there should be a way in actor to verify in runtime if the same type of component is being injected more than once in the same actor. This map holds a list of {key, value} pairs where the keys are possible components and the values default to false which means that the associated component has not yet been injected in the actor.
  std::unordered_map<std::string, bool> mComponentMap
  {
    {"TransformComponent", false},
    {"SpriteComponent", false},
  };
};

}

