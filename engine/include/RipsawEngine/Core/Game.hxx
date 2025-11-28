#pragma once

namespace RipsawEngine
{

class Game
{
public:
  /// Default constructor for Game.
  /// @details The philosophy as of now for the engine is, engine code and game code must have a clear line between them. Engine would act as an operating system for game, maintaining all low level subsystems and calculations. Engine would have no idea about what a game is. It would just run the main loop which would update and render all necessary systems. As the engine's update and render code would be locked down, it would be impossible to design and inject custom update code to entities. This class acts as a solution to that. It exposes some virtual API which can be extended in sandbox code to inject custom entity behavior in the engine. Game is instantiated in sandbox, then Engine receives a pointer to Game instance. Engine internally calls Game's virtual APIs in appropriate places which enables integration of custom entity behavior without touching engine code. Game also needs access to Engine instance which it receives in Engine's internal implementation via the setEngine() method.
  Game() = default;
  /// Sets mEngine with pointer to Engine instance.
  /// @param engine Pointer to @ref Engine instance.
  void setEngine(class Engine* engine);
  /// Custom initialization logic for Game.
  virtual void initGame();
  /// Custom update logic for Game.
  virtual void updateGame(double dt);
  /// Custom render logic for Game.
  virtual void renderGame();

public:
  /// Pointer to main Engine instance.
  class Engine* mEngine{nullptr};
};

}

