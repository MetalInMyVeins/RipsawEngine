#ifndef SCENE_TRANSFORMCOMPONENT_HXX
#define SCENE_TRANSFORMCOMPONENT_HXX

#include <glm/glm.hpp>

#include "Component.hxx"

namespace RipsawEngine
{

class TransformComponent : public Component
{
public:
  /// @brief Constructs transform component with owning actor, position, and velocity.
  /// @param actor Owning actor of transform component.
  /// @param pos Position of actor.
  /// @param vel Velocity of actor.
  TransformComponent(class Actor* actor, const glm::vec2& pos = {}, const glm::vec2& vel = {});
  /// Destructs transform component.
  ~TransformComponent();
  /// Checks if TransformComponent is valid.
  bool isComponentValid() const override;
  /// Updates transform component.
  /// @param dt Delta-time.
  void update(double dt) override;
  /// Returns position.
  glm::vec2 getPosition() const;
  /// Sets position.
  /// @param pos Position.
  void setPosition(const glm::vec2& pos);
  /// Returns velocity.
  glm::vec2 getVelocity() const;
  /// Sets velocity.
  /// @param vel Velocity.
  void setVelocity(const glm::vec2& vel);

private:
  /// Position.
  glm::vec2 mPos{};
  /// Velocity.
  glm::vec2 mVel{};
};

}

#endif

