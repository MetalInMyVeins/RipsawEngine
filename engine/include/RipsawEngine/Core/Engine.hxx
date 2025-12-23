#pragma once

#include <string>
#include <utility>
#include <vector>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <glm/glm.hpp>

namespace RipsawEngine
{

class Engine
{
public:
  /// @brief Constructs engine with Game* object, configurable window name and size.
  /// @param game Pointer to @ref Game instance
  /// @param wname Custom window name.
  /// @param w Custom window width.
  /// @param h Custom window height.
  Engine(class Game* game, const std::string& wname = "RipsawEngine", int w = 0, int h = 0);
  /// Destructs engine.
  ~Engine();
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  Engine(Engine&&) = delete;
  Engine& operator=(Engine&&) = delete;
  /// @brief Initializes video, audio, window, renderer etc.
  /// @return True if successful, False otherwise.
  bool init();
  /// @brief Runs the main game loop.
  void run();
  /// @brief Frees resources and prepares for program shutdown.
  void shutdown();
  /// Returns mRenderer.
  SDL_Renderer* getRenderer() const;
  /// Returns screen size in a pair.
  std::pair<int, int> getScreenSize() const;
  /// Sets renderer backend mRendererBackend of engine.
  /// @details Current valid values are: opengl, vulkan, software.
  /// @param backend Renderer backend.
  void setRendererBackend(const std::string& backend);

private:
  /// @brief Processes inputs.
  void processInput();
  /// @brief Updates the game world.
  void updateEngine();
  /// @brief Renders game output on screen.
  void renderEngine();

private:
  /// Window name.
  std::string mWname{};
  /// Screen width.
  int mScreenWidth{};
  /// Screen height.
  int mScreenHeight{};
  /// True if screen size has been manually configured.
  bool mIsDisplaySetManually{false};
  /// True if game loop is running.
  bool mIsRunning{true};
  /// Window pointer.
  SDL_Window* mWindow{nullptr};
  /// Renderer pointer.
  SDL_Renderer* mRenderer{nullptr};
  /// Renderer backend for engine.
  std::string mRendererBackend{"opengl"};
  /// Delta time.
  double mDt{};
  /// Ticks passed since last frame.
  Uint64 mTicksCount{};
  /// Timer denoting if 1 second has passed.
  double mtimer{};
  /// Frames per second.
  int mFrames{};

public:
  /// Dynamically allocates actor.
  /// @details This is a high level virtual member function to be called from sandbox to create actor. It returns pointer to the allocated actor for custom manipulation. The returned pointer should never be deleted explicitly as Engine handles the ownership. An actor should only be detroyed using destroyActor() when needed. After destroyActor() is called on an actor, trying to dereference that actor would result in crash as the actor is nullified.
  /// @return Returns pointer to the allocated actor.
  virtual class Actor* createActor();
  /// Destroys specified actor by deleting and removing it from mActors and nullifying it.
  /// @param actor Actor to be destroyed.
  void destroyActor(class Actor*& actor);
  /// Adds actor to @ref mActors.
  /// @param actor Pointer to @ref Actor instance.
  void addActor(class Actor* actor);
  /// Removes actor from @ref mActors.
  /// @param actor Pointer to @ref Actor instance.
  void removeActor(class Actor* actor);
  /// Adds @ref SpriteComponent to mSprites.
  /// @details @ref renderEngine() calls draw() method of SpriteComponent which handles drawing on screen. SpriteComponent gets @ref TransformComponent from actor which ties the sprite with the actor. Successful construction of SpriteComponent automatically calls this method so explicit calling is not needed.
  /// @param sc Sprite component.
  void addSprite(class SpriteComponent* sc);
  /// Removes @ref SpriteComponent from mSprites.
  /// @param sc Sprite component.
  void removeSprite(class SpriteComponent* sc);

private:
  /// Extendible Game class.
  class Game* mGame{nullptr};
  /// List of all actors.
  std::vector<class Actor*> mActors{};
  /// List of all sprites to be drawn.
  std::vector<class SpriteComponent*> mSprites{};
  /// Total size of all registered actors.
  size_t mTotalActorsSize{};
};

}

