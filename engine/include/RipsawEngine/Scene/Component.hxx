#pragma once

namespace RipsawEngine
{

class Component
{
public:
  /// Constructs component with pointer to @ref Actor instance.
  /// @param actor Actor owning the component.
  Component(class Actor* actor);
  /// Destructor.
  virtual ~Component();
  /// Pointer to actor owning the component.
  class Actor* mOwner{nullptr};
  /// Updates component.
  /// @param dt Delta-time.
  virtual void update(double dt);
};

}

