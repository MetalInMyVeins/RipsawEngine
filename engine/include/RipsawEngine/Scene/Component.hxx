#pragma once

namespace RipsawEngine
{

class Component
{
public:
  /// @brief Constructs component with pointer to @ref Actor instance.
  /// @details This is an abstract base class for defining components. All derived components must implement @ref isComponentValid(). This provides a way for instantiated component to mark themselves valid or invalid based on certain conditions. If a derived component is surely a valid component, then @ref isComponentValid() should just return True.
  /// @param actor Actor owning the component.
  Component(class Actor* actor);
  Component(const Component&) = delete;
  Component& operator=(const Component&) = delete;
  Component(Component&&) = delete;
  Component& operator=(Component&&) = delete;
  /// Destructs component.
  virtual ~Component();
  /// Pointer to actor owning the component.
  class Actor* mOwner{nullptr};
  /// Updates component.
  /// @param dt Delta-time.
  virtual void update(double dt);
  /// Overridable method that says if a specific component is valid.
  /// @return True if valid, False otherwise.
  virtual bool isComponentValid() const = 0;
};

}

