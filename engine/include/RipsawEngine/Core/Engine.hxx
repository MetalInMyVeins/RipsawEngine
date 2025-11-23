#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

namespace RipsawEngine
{

class Engine
{
public:
  /// @brief Constructs engine with configurable window size.
  /// @param w Custom window width
  /// @param h Custom window height
  Engine(int w = 0, int h = 0);
  /// @brief Initializes video, audio, window, renderer etc.
  /// @return True if successful, False otherwise.
  bool init();
  /// @brief Runs the main game loop.
  void run();
  /// @brief Frees resources and prepares for program shutdown.
  void shutdown();

private:
  /// @brief Processes inputs.
  void processInput();
  /// @brief Updates the game world.
  void updateEngine();
  /// @brief Renders game output on screen.
  void renderEngine();
  /// @brief Loads game assets.
  bool loadMedia();
  /// @brief Unloads game assets.
  void unloadMedia();

private:
  /// Screen width
  int mScreenWidth{};
  /// Screen height
  int mScreenHeight{};
  /// True if screen size has been manually configured
  bool mIsDisplaySetManually{false};
  /// True if game loop is running
  bool mIsRunning{true};
  /// Window pointer
  SDL_Window* mWindow{nullptr};
  /// Renderer pointer
  SDL_Renderer* mRenderer{nullptr};
  /// Ticks passed since last frame
  Uint64 mTicksCount{};
  /// Timer denoting if 1 second has passed
  double mtimer{};
  /// Frames per second
  int mFrames{};

public:
  /// Adds actor to @ref mActors.
  /// @param actor Pointer to @ref Actor instance.
  void addActor(class Actor* actor);
  /// Removes actor from @ref mActors.
  /// @param actor Pointer to @ref Actor instance.
  void removeActor(class Actor* actor);

private:
  /// List of all actors
  std::vector<class Actor*> mActors{};
};

}

