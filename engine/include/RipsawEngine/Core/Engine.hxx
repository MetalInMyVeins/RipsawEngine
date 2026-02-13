#ifndef CORE_ENGINE_HXX
#define CORE_ENGINE_HXX

#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>

#include "RipsawEngine/Core/Timer.hxx"

namespace RipsawEngine
{

/// Variant type for all possible manager classes.
using AnyManager = std::variant<
  class BGManager*
>;

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
  virtual ~Engine();
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  Engine(Engine&&) = delete;
  Engine& operator=(Engine&&) = delete;
  /// Engine timer.
  Timer mTimer{};
  /// @brief Initializes video, audio, window, renderer etc.
  /// @return True if successful, False otherwise.
  bool init();
  /// @brief Runs the main game loop.
  void run();
  /// @brief Frees resources and prepares for program shutdown.
  void shutdown();
  /// Pauses engine by pausing the timer.
  /// @details Every actor updates as a function of dt. When timer is paused, dt becomes 0 and all actor freeze.
  void pauseEngine();
  /// Resumes engine.
  void resumeEngine();
  /// Toggles between pausing and resuming engine.
  void enginePauseResumeToggle();
  /// Returns mRenderer.
  SDL_Renderer* getRenderer() const;
  /// Returns screen size in a pair.
  std::pair<int, int> getScreenSize() const;
  /// Returns delta-time.
  double getDt() const;
  /// Enables/disables vsync.
  /// @param vsync Boolean vsync value.
  void setVsync(bool vsync);
  /// Sets renderer backend mRendererBackend of engine. Defaults to opengl.
  /// @details Current valid values are: opengl, vulkan, software.
  /// @param backend Renderer backend.
  void setRendererBackend(const std::string& backend = "opengl");

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
  double mFrameTime{};
  /// Frames per second.
  int mFrames{};
  /// Delta-time clamp value clamped to 60 FPS dt equivalent.
  const double mDtClamp{static_cast<double>(1) / 60};
  bool mVsyncEnabled{true};

public:
  /// Dynamically allocates actor.
  /// @details This is a high level virtual member function to create actor. It returns pointer to the allocated actor for custom manipulation. The returned pointer should never be deleted manually as Engine handles the ownership. An actor should only be detroyed using destroyActor() when needed. After destroyActor() is called on an actor, trying to dereference that actor would result in crash as the actor would be nullified. So it's highly recommended to do any operation on the returned Actor pointer by checking if it's nullptr.
  /// @return Returns pointer to the allocated actor.
  virtual class Actor* createActor();
  /// Destroys specified actor by deleting and removing it from mActors, nullifying at the end.
  /// @details This method removes specified actor from mActors. But if removal occurs while actors are going through the update loop, this might crash the engine. To prevent that, a boolean signal mActorsBeingUpdated is introduced which is set before entering the update loop and unset after exiting the loop. The method first checks if the signal is set. If unset, it destroys the actor right away. But if set, it pushes the actor in another vector mActorsToBeKilled. Then, this method is called again on every actors of mActorsToBeKilled before entering the update loop.
  /// @param actor Adress of actor to be destroyed.
  void destroyActor(class Actor** actor);
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
  /// Inserts Actor-SpriteComponent pair into mActorSpritePairs.
  /// @param asp Actor-SpriteComponent pair.
  void insertActorSpritePair(const std::pair<class Actor*, class Component*>& asp);
  /// Removes Actor-SpriteComponent pair from mActorSpritePairs.
  /// @param actor Actor key to be removed from mActorSpritePairs.
  void removeActorSpritePair(class Actor* actor);
  /// Helper method to create BGManager with specified layers and speeds.
  /// @warning Throws runtime error if number of layers and number of speeds doesn't equate.
  /// @param layers Images of each layer.
  /// @param layerSpeeds Speed values of each layers.
  class BGManager* createBGManager(const std::vector<std::string>& layers, const std::vector<float>& layerSpeeds);

public:
  /// Boolean signal depicting if actors are going through update loop.
  bool mActorsBeingUpdated{false};

public:
  /// Moves sprite component associated with first actor below the sprite component associated with second actor in mSprites.
  /// @details This member function directly manipulates the order of sprite components in mSprites.
  /// @param a1 Actor to be moved.
  /// @param a2 Actor below which a1 would go to.
  void actorGoesBelow(class Actor* a1, class Actor* a2);
  /// Moves sprite component associated with first actor above the sprite component associated with second actor in mSprites.
  /// @details This member function directly manipulates the order of sprite components in mSprites.
  /// @param a1 Actor to be moved.
  /// @param a2 Actor above which a1 would go to.
  void actorGoesAbove(class Actor* a1, class Actor* a2);

private:
  /// Extendible Game class.
  class Game* mGame{nullptr};
  /// List of all actors.
  std::vector<class Actor*> mActors{};
  /// List of actors that are to be killed before next actor update begins.
  std::vector<class Actor**> mActorsToBeKilled{};
  /// List of all sprites to be drawn.
  std::vector<class SpriteComponent*> mSprites{};
  /// Total size of all registered actors.
  size_t mTotalActorsSize{};
  /// List of Actor-SpriteComponent pairs associated with each other.
  std::unordered_map<class Actor*, class Component*> mActorSpritePairs{};
  /// List of all managers.
  std::vector<AnyManager> mManagers{};
};

}

#endif

