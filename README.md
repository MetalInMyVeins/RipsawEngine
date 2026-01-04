# RipsawEngine

2D/3D game engine being implemented from scratch in C++. This is a pet project and I work on it in my free time, for fun. Grew up playing lots of games and it's been quite some time I have been wishing to write my own engine. As I enjoy understanding and working on complex systems, this is the perfect type of project to have fun from. So, seeing where it goes.

# Dependencies

- SDL3
- GLM
- GCC/Clang/Any C++ 20 compatible compiler
- CMake

### Optional Dependencies

- Doxygen (for documentation)
- GNU `tree` (for directory layout)
- Ninja (for faster build)
- Python 3 (for parsing documentation)
- GNU Binutils (for `strip`)
- `upx` (for compressing binary)
- `libc++` (for better compliance with sanitizers)
- `libc++abi`
- `lld` (for clang-specific builds)
- `valgrind` (for leak detection)

# Directory Layout

<!-- AUTODOC:BEGIN -->

```
.
├── CMakeLists.txt
├── Doxyfile
├── LICENSE.md
├── README.md
├── README.template.md
├── build.sh
├── engine
│   ├── CMakeLists.txt
│   ├── include
│   │   └── RipsawEngine
│   │       ├── Core
│   │       │   ├── Core.hxx
│   │       │   ├── Engine.hxx
│   │       │   └── Game.hxx
│   │       ├── Managers
│   │       │   ├── BGManager.hxx
│   │       │   └── Managers.hxx
│   │       └── Scene
│   │           ├── Actor.hxx
│   │           ├── Component.hxx
│   │           ├── Scene.hxx
│   │           ├── SpriteComponent.hxx
│   │           ├── SpritesheetComponent.hxx
│   │           └── TransformComponent.hxx
│   └── src
│       ├── Actor.cxx
│       ├── BGManager.cxx
│       ├── Component.cxx
│       ├── Engine.cxx
│       ├── Game.cxx
│       ├── SpriteComponent.cxx
│       ├── SpritesheetComponent.cxx
│       ├── TransformComponent.cxx
│       ├── processInput.cxx
│       ├── renderEngine.cxx
│       └── updateEngine.cxx
├── sandbox
│   ├── CMakeLists.txt
│   ├── assets
│   │   ├── bglayer1.png
│   │   ├── bglayer2.png
│   │   ├── ships1.png
│   │   └── ships2.png
│   └── src
│       └── main.cxx
├── scripts
│   └── gen_docs.py
└── supp
    └── tsan.supp

13 directories, 37 files

```

<!-- AUTODOC:END -->

# Project Components

- `engine/`: All engine code goes here.
- `sandbox/`: All engine feature testing code goes here.
- `scripts/`: All supplementary scripts go here.
- `supp/`: All suppression files go here. Suppression files are files to suppress errors from libraries that are out of scope of the engine.

# Features

Features in the engine are added incrementally. And each commit contains a demo of the feature in sandbox which can be built and run. Engine is still in zygote phase, so not a lot of features as of now. The notable features for now include but are not limited to:

- Actor-Component system
- Strong ownership model
- Clear separation of engine code and game code
- 2D rendering pipeline
- Flexible but strict build system
- Sanitizer-aware debug builds by default (ASan, UBSan, TSan)
- Strict compliance with C++ standard
- Detailed documentation of engine code

# TODO

- Controlled sprite draw order (complete)
- Spritesheet support (complete)
- Sprite animation (in progress)

# Building

`build.sh` is provided for easier building of engine and sandbox demo providing multiple build options. The demo binary path after building is `sandbox/bin/sandbox`. Examples:

```bash
# For debug build with libstdc++ (works well with valgrind)
./build.sh
# For debug build with libc++
./build.sh --libcxx
# For debug build with ASan + UBSan
./build.sh --aubsan
# For debug build with MSan
./build.sh --msan
# For debug build with TSan
./build.sh --tsan
# For release build
./build.sh --release
# For building with gcc (default is clang)
./build.sh --gcc
# For release build with gcc
./build.sh --gcc --release
```

<details>
<summary><h1>API Documentation</h1></summary>

<!-- AUTODOC:BEGIN -->

## RipsawEngine::Actor

### Member Variables

- `class Engine*` `mEngine`: Main engine instance.
- `std::vector<class Component*>` `mComponents`: Vector of all components tied to the actor.
- `class TransformComponent*` `mTransformComponent`: TransformComponent tied to the actor (if any).
- `class SpriteComponent*` `mSpriteComponent`: SpriteComponent tied to the actor (if any).
- `std::unordered_map<std::string, bool>` `mComponentMap`: Map of all possible components that actor can hold and their inclusion status in the actor.
  
  Components are capabilities of an actor. The philosophy as of now is, no actor should be able to hold the same type of component more than once. To ensure that, there should be a way in actor to verify in runtime if the same type of component is being injected more than once in the same actor. This map holds a list of {key, value} pairs where the keys are possible components and the values default to false which means that the associated component has not yet been injected in the actor.

### Member Functions

#### `RipsawEngine::Actor::Actor`

Constructs actor with pointer to Engine instance.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `engine` | `class Engine *` | Pointer to Engine instance. |

#### `RipsawEngine::Actor::Actor`

#### `Actor & RipsawEngine::Actor::operator=`

#### `RipsawEngine::Actor::Actor`

#### `Actor & RipsawEngine::Actor::operator=`

#### `RipsawEngine::Actor::~Actor`

Destructs actor.

#### `void RipsawEngine::Actor::update`

Updates actor.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `dt` | `double` | Delta-time. |

#### `void RipsawEngine::Actor::updateComponents`

Updates all components tied to the actor.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `dt` | `double` | Delta-time. |

#### `void RipsawEngine::Actor::addComponent`

Adds component to actor storing in mComponents .

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `component` | `class Component *` | Component to be added to actor. |

#### `void RipsawEngine::Actor::removeComponent`

Removes component from actor.

As of now, this function is not needed because actor would automatically destroy all owned components upon destruction.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `component` | `class Component *` | Component to be removed from actor. |

#### `TransformComponent * RipsawEngine::Actor::getTransformComponent`

Returns mTransformComponent .

This method works as a way for other components or entities to get access to TransformComponent .

#### `void RipsawEngine::Actor::setTransformComponent`

Sets mTransformComponent .

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `tc` | `class TransformComponent *` | Transform component. |

#### `SpriteComponent * RipsawEngine::Actor::getSpriteComponent`

Returns mSpriteComponent .

This method works as a way for other components or entities to get access to SpriteComponent .

#### `void RipsawEngine::Actor::setSpriteComponent`

Sets mSpriteComponent.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `sc` | `class SpriteComponent *` | Sprite component. |

#### `glm::vec2 RipsawEngine::Actor::getPosition`

Returns position of actor.

#### `void RipsawEngine::Actor::setPosition`

Sets position of actor.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `pos` | `const glm::vec2 &` | Position of actor. |

#### `glm::vec2 RipsawEngine::Actor::getVelocity`

Sets velocity of actor.

#### `void RipsawEngine::Actor::setVelocity`

Sets velocity of actor.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `vel` | `const glm::vec2 &` | Velocity of actor. |

#### `Engine * RipsawEngine::Actor::getEngine`

Returns mEngine so that other componets can use it if needed.

#### `bool RipsawEngine::Actor::hasComponent`

Returns True if the specified component exists in mComponentMap.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `compname` | `const std::string &` | Component name. |

#### `void RipsawEngine::Actor::registerComponent`

Registers specified component in mComponentMap.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `compname` | `const std::string &` | Component name. |

#### `void RipsawEngine::Actor::deregisterComponent`

Deregisters component from mComponentMap.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `compname` | `const std::string &` | Component name. |

#### `void RipsawEngine::Actor::helperRegisterComponent`

Helper method to ease out component registration avoiding code duplication.

@warn Throws runtime error if specified component has already been injected in actor.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `compname` | `const std::string &` | Component name. |

#### `void RipsawEngine::Actor::createTransformComponent`

Dynamically allocates TransformComponent .

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `pos` | `const glm::vec2 &` | Position of actor. |
| `vel` | `const glm::vec2 &` | Velocity of actor. |

#### `void RipsawEngine::Actor::createSpriteComponent`

Dynamically allocates SpriteComponent .

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `imgfile` | `const std::string &` | Image file for sprite. |

#### `void RipsawEngine::Actor::createSpriteComponent`

Dynamically allocates SpriteComponent .

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `size` | `const glm::vec2 &` | Size of sprite. |
| `color` | `const std::tuple< unsigned char, unsigned char, unsigned char, unsigned char > &` | Color of sprite. |

#### `void RipsawEngine::Actor::createSpritesheetComponent`

Dynamically allocates SpritesheetComponent .

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `imgfile` | `const std::string &` | Image file for sprite. |
| `dims` | `const glm::vec2 &` | Dimension of spritesheet {col, row}. |
| `defaultCoord` | `const glm::vec2 &` | Default coordinate of spritesheet for rendering. |


---

## RipsawEngine::BGManager

### Member Variables

- `class Engine*` `mEngine`: Pointer to Engine instance.
- `std::vector<std::string>` `mLayers`: Layers of background images.
- `std::vector<float>` `mLayerSpeeds`: Speed of background layers.
- `std::vector<std::tuple<class Actor*, class Actor*, class Actor*> >` `mActorTriplets`: Vector of Actor triplet.

### Member Functions

#### `RipsawEngine::BGManager::BGManager`

Constructs BGManager with Engine*, background image layers, and the speed of each layer.

This is a manager class. The purpose of manager classes are to create and manage already-programmed entities to complete a certain task. This background manager class implements parallax scrolling background with layers of provided images and their speeds. The philosophy is, any both-way scrolling 2D infinite background can be implemented with at least three actors. So, there would be a triplet of actors per layer which would be placed side by side to each other. The middle actor would be placed at the center of the screen, right one to its right, and left one to its left. Each actor would receive the same layer sprite. When the middle actor would go out of screen bound, its left or right actor would be repositioned to the right or left depending on scroll direction creating the illusion of infinite scrolling. The procedure is applied to all layers. And each layer would move at the speed of their respective speed.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `engine` | `class Engine *` | Pointer to Engine instance. |
| `layers` | `const std::vector< std::string > &` | Layers of background images. |
| `layerSpeeds` | `const std::vector< float > &` | Vector of layer speed. |

#### `void RipsawEngine::BGManager::update`

Implements custom update logic for manager.

#### `void RipsawEngine::BGManager::setSpeeds`

Sets scrolling speed of layers.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `speeds` | `const std::vector< float > &` | Vector of speed values of layers. |

#### `void RipsawEngine::BGManager::changeSpeedBy`

Changes scrolling speed of layers by specified amount of speed.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `dx` | `float` | Speed to change in X-axis. |
| `dy` | `float` | Speed to change in Y-axis. |


---

## RipsawEngine::Component

### Member Variables

- `class Actor*` `mOwner`: Pointer to actor owning the component.

### Member Functions

#### `RipsawEngine::Component::Component`

Constructs component with pointer to Actor instance.

This is an abstract base class for defining components. All derived components must implement isComponentValid() . This provides a way for instantiated component to mark themselves valid or invalid based on certain conditions. If a derived component is surely a valid component, then isComponentValid() should just return True.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor *` | Actor owning the component. |

#### `RipsawEngine::Component::Component`

#### `Component & RipsawEngine::Component::operator=`

#### `RipsawEngine::Component::Component`

#### `Component & RipsawEngine::Component::operator=`

#### `RipsawEngine::Component::~Component`

Destructs component.

#### `void RipsawEngine::Component::update`

Updates component.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `dt` | `double` | Delta-time. |

#### `virtual bool RipsawEngine::Component::isComponentValid`

Overridable method that says if a specific component is valid.

#### Return

| Type | Description |
|--------|-------------|
| bool | True if valid, False otherwise. |


---

## RipsawEngine::SpriteComponent

### Member Variables

- `SDL_Renderer*` `mRenderer`: Renderer.
- `std::string` `mImgFile`: Image file path.
- `SDL_Texture*` `mTexture`: Main texture.
- `glm::vec2` `mTexSize`: Texture size.
- `glm::vec2` `mTexSizeDynamic`: Modified texture dimension after scale change.
- `float` `mScale`: Texture scale.
- `double` `mRotationSpeed`: Speed of rotation (degree) controlling how fast to rotate sprite.
- `double` `mRotationAmount`: The amount of rotation (degree) to take effect in texture.
- `bool` `mHasRotated`: Boolean flag to track if sprite has rotated.
- `SDL_FlipMode` `mFlipState`: Current flip state of sprite.

### Member Functions

#### `RipsawEngine::SpriteComponent::SpriteComponent`

Constructs sprite component with owning actor, renderer, and image file.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor *` | Actor owning the component. |
| `renderer` | `SDL_Renderer *` | Renderer. |
| `imgfile` | `const std::string &` | Path to image file. |

#### `RipsawEngine::SpriteComponent::SpriteComponent`

Constructs sprite component with owning actor, renderer, rectangle size, and color.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor *` | Actor owning the component. |
| `renderer` | `SDL_Renderer *` | Renderer. |
| `size` | `const glm::vec2 &` | Pair of float containing rectangle width and height. |
| `color` | `const std::tuple< unsigned char, unsigned char, unsigned char, unsigned char > &` | Tuple of RGBA color values. |

#### `RipsawEngine::SpriteComponent::~SpriteComponent`

Destructs SpriteComponent .

#### `bool RipsawEngine::SpriteComponent::isComponentValid`

Checks if SpriteComponent is valid.

#### `SDL_Texture * RipsawEngine::SpriteComponent::getTexture`

Returns mTexture.

#### `glm::vec2 RipsawEngine::SpriteComponent::getTexSize`

Returns texture size.

#### `void RipsawEngine::SpriteComponent::draw`

Draws texture on window.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `dt` | `double` | Delta-time. |

#### `float RipsawEngine::SpriteComponent::getScale`

Returns scale of texture.

#### `void RipsawEngine::SpriteComponent::setScale`

Sets scale of texture.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `scale` | `float` | Texture scale. |

#### `double RipsawEngine::SpriteComponent::getRotationAmount`

Returns amount of rotation mRotationAmount.

#### `double RipsawEngine::SpriteComponent::getRotationSpeed`

Returns rotation speed mRotationSpeed.

#### `void RipsawEngine::SpriteComponent::setRotationSpeed`

Sets rotation speed mRotationSpeed.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `rotation` | `double` | Rotation speed per second in degrees by which rotation amount would be incremented/decremented. |

#### `void RipsawEngine::SpriteComponent::rotateClockwiseAmount`

Rotates sprite clockwise by specified degrees.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `degrees` | `double` | Angle in degrees by which sprite would be rotated. |

#### `void RipsawEngine::SpriteComponent::rotateAntiClockwiseAmount`

Rotates sprite anti-clockwise by specified degrees.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `degrees` | `double` | Angle in degrees by which sprite would be rotated. |

#### `void RipsawEngine::SpriteComponent::flipHorizontally`

Flips sprite horizontally unless any rotation has occurred.

#### `void RipsawEngine::SpriteComponent::flipVertically`

Flips sprite vertically unless any rotation has occurred.

#### `void RipsawEngine::SpriteComponent::flipDefault`

Sets flip state to default.

#### `void RipsawEngine::SpriteComponent::changeCoord`

Virtual function to be called from SpritesheetComponent .

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `coord` | `const glm::vec2 &` |  |

#### `void RipsawEngine::SpriteComponent::fitByAspectRatio`

Fits sprite covering entire screen preserving aspect ratio.

#### `void RipsawEngine::SpriteComponent::normalizeDegrees`

Normalizes angle in [0, 360) range.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `degrees` | `double &` | Angle in degrees to be normalized. |

#### `void RipsawEngine::SpriteComponent::setRotationAmount`

Sets amount of rotation.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `rotationAmount` | `double` | Amount of rotation. |

#### `SDL_Renderer * RipsawEngine::SpriteComponent::getRenderer`

Returns renderer mRenderer.

#### `SDL_FlipMode RipsawEngine::SpriteComponent::getFlipState`

Returns flip state mFlipState.


---

## RipsawEngine::SpritesheetComponent

### Member Variables

- `glm::vec2` `mDims`: Dimension of spritesheet in {col, row} where col is number of sprites horizontally, and row is number of sprites vertically.
- `glm::vec2` `mDefaultCoord`: Default coordinate of spritesheet.

### Member Functions

#### `RipsawEngine::SpritesheetComponent::SpritesheetComponent`

Constructs spritesheet component with owning actor, renderer, spritesheet image, dimension of spritesheet, and default rendering coordinate of spritesheet.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor *` | Actor owning the component. |
| `renderer` | `SDL_Renderer *` | Renderer. |
| `imgfile` | `const std::string &` | Path to image file. |
| `dims` | `const glm::vec2 &` | Dimension of spritesheet. |
| `defaultCoord` | `const glm::vec2 &` | Default coordinate of spritesheet. |

#### `void RipsawEngine::SpritesheetComponent::draw`

Draws texture on window.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `dt` | `double` | Delta-time. |

#### `void RipsawEngine::SpritesheetComponent::changeCoord`

Changes default coordinate of spritesheet.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `coord` | `const glm::vec2 &` |  |


---

## RipsawEngine::TransformComponent

### Member Variables

- `glm::vec2` `mPos`: Position.
- `glm::vec2` `mVel`: Velocity.

### Member Functions

#### `RipsawEngine::TransformComponent::TransformComponent`

Constructs transform component with owning actor, position, and velocity.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor *` | Owning actor of transform component. |
| `pos` | `const glm::vec2 &` | Position of actor. |
| `vel` | `const glm::vec2 &` | Velocity of actor. |

#### `RipsawEngine::TransformComponent::~TransformComponent`

Destructs transform component.

#### `bool RipsawEngine::TransformComponent::isComponentValid`

Checks if TransformComponent is valid.

#### `void RipsawEngine::TransformComponent::update`

Updates transform component.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `dt` | `double` | Delta-time. |

#### `glm::vec2 RipsawEngine::TransformComponent::getPosition`

Returns position.

#### `void RipsawEngine::TransformComponent::setPosition`

Sets position.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `pos` | `const glm::vec2 &` | Position. |

#### `glm::vec2 RipsawEngine::TransformComponent::getVelocity`

Returns velocity.

#### `void RipsawEngine::TransformComponent::setVelocity`

Sets velocity.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `vel` | `const glm::vec2 &` | Velocity. |


---

## RipsawEngine::Engine

### Member Variables

- `std::string` `mWname`: Window name.
- `int` `mScreenWidth`: Screen width.
- `int` `mScreenHeight`: Screen height.
- `bool` `mIsDisplaySetManually`: True if screen size has been manually configured.
- `bool` `mIsRunning`: True if game loop is running.
- `SDL_Window*` `mWindow`: Window pointer.
- `SDL_Renderer*` `mRenderer`: Renderer pointer.
- `std::string` `mRendererBackend`: Renderer backend for engine.
- `double` `mDt`: Delta time.
- `Uint64` `mTicksCount`: Ticks passed since last frame.
- `double` `mtimer`: Timer denoting if 1 second has passed.
- `int` `mFrames`: Frames per second.
- `class Game*` `mGame`: Extendible Game class.
- `std::vector<class Actor*>` `mActors`: List of all actors.
- `std::vector<class Actor**>` `mActorsToBeKilled`: List of actors that are to be killed before next actor update begins.
- `std::vector<class SpriteComponent*>` `mSprites`: List of all sprites to be drawn.
- `size_t` `mTotalActorsSize`: Total size of all registered actors.
- `std::unordered_map<class Actor*, class Component*>` `mActorSpritePairs`: List of Actor-SpriteComponent pairs associated with each other.
- `std::vector<AnyManager>` `mManagers`: List of all managers.
- `bool` `mActorsBeingUpdated`: Boolean signal depicting if actors are going through update loop.

### Member Functions

#### `RipsawEngine::Engine::Engine`

Constructs engine with Game* object, configurable window name and size.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `game` | `class Game *` | Pointer to Game instance |
| `wname` | `const std::string &` | Custom window name. |
| `w` | `int` | Custom window width. |
| `h` | `int` | Custom window height. |

#### `RipsawEngine::Engine::~Engine`

Destructs engine.

#### `RipsawEngine::Engine::Engine`

#### `Engine & RipsawEngine::Engine::operator=`

#### `RipsawEngine::Engine::Engine`

#### `Engine & RipsawEngine::Engine::operator=`

#### `bool RipsawEngine::Engine::init`

Initializes video, audio, window, renderer etc.

#### Return

| Type | Description |
|--------|-------------|
| bool | True if successful, False otherwise. |

#### `void RipsawEngine::Engine::run`

Runs the main game loop.

#### `void RipsawEngine::Engine::shutdown`

Frees resources and prepares for program shutdown.

#### `SDL_Renderer * RipsawEngine::Engine::getRenderer`

Returns mRenderer.

#### `std::pair< int, int > RipsawEngine::Engine::getScreenSize`

Returns screen size in a pair.

#### `double RipsawEngine::Engine::getDt`

Returns delta-time.

#### `void RipsawEngine::Engine::setRendererBackend`

Sets renderer backend mRendererBackend of engine.

Defaults to opengl.  Current valid values are: opengl, vulkan, software.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `backend` | `const std::string &` | Renderer backend. |

#### `Actor * RipsawEngine::Engine::createActor`

Dynamically allocates actor.

This is a high level virtual member function to create actor. It returns pointer to the allocated actor for custom manipulation. The returned pointer should never be deleted manually as Engine handles the ownership. An actor should only be detroyed using destroyActor() when needed. After destroyActor() is called on an actor, trying to dereference that actor would result in crash as the actor would be nullified. So it's highly recommended to do any operation on the returned Actor pointer by checking if it's nullptr.

#### Return

| Type | Description |
|--------|-------------|
| class Actor * | Returns pointer to the allocated actor. |

#### `void RipsawEngine::Engine::destroyActor`

Destroys specified actor by deleting and removing it from mActors, nullifying at the end.

This method removes specified actor from mActors. But if removal occurs while actors are going through the update loop, this might crash the engine. To prevent that, a boolean signal mActorsBeingUpdated is introduced which is set before entering the update loop and unset after exiting the loop. The method first checks if the signal is set. If unset, it destroys the actor right away. But if set, it pushes the actor in another vector mActorsToBeKilled. Then, this method is called again on every actors of mActorsToBeKilled before entering the update loop.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor **` | Adress of actor to be destroyed. |

#### `void RipsawEngine::Engine::addActor`

Adds actor to mActors .

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor *` | Pointer to Actor instance. |

#### `void RipsawEngine::Engine::removeActor`

Removes actor from mActors .

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor *` | Pointer to Actor instance. |

#### `void RipsawEngine::Engine::addSprite`

Adds SpriteComponent to mSprites.

renderEngine() calls draw() method of SpriteComponent which handles drawing on screen. SpriteComponent gets TransformComponent from actor which ties the sprite with the actor. Successful construction of SpriteComponent automatically calls this method so explicit calling is not needed.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `sc` | `class SpriteComponent *` | Sprite component. |

#### `void RipsawEngine::Engine::removeSprite`

Removes SpriteComponent from mSprites.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `sc` | `class SpriteComponent *` | Sprite component. |

#### `void RipsawEngine::Engine::insertActorSpritePair`

Inserts Actor-SpriteComponent pair into mActorSpritePairs.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `asp` | `const std::pair< class Actor *, class Component * > &` | Actor-SpriteComponent pair. |

#### `void RipsawEngine::Engine::removeActorSpritePair`

Removes Actor-SpriteComponent pair from mActorSpritePairs.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor *` | Actor key to be removed from mActorSpritePairs. |

#### `BGManager * RipsawEngine::Engine::createBGManager`

Helper method to create BGManager with specified layers and speeds.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `layers` | `const std::vector< std::string > &` | Images of each layer. |
| `layerSpeeds` | `const std::vector< float > &` | Speed values of each layers. |

#### `void RipsawEngine::Engine::actorGoesBelow`

Moves sprite component associated with first actor below the sprite component associated with second actor in mSprites.

This member function directly manipulates the order of sprite components in mSprites.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `a1` | `class Actor *` | Actor to be moved. |
| `a2` | `class Actor *` | Actor below which a1 would go to. |

#### `void RipsawEngine::Engine::actorGoesAbove`

Moves sprite component associated with first actor above the sprite component associated with second actor in mSprites.

This member function directly manipulates the order of sprite components in mSprites.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `a1` | `class Actor *` | Actor to be moved. |
| `a2` | `class Actor *` | Actor above which a1 would go to. |

#### `void RipsawEngine::Engine::processInput`

Processes inputs.

#### `void RipsawEngine::Engine::updateEngine`

Updates the game world.

#### `void RipsawEngine::Engine::renderEngine`

Renders game output on screen.


---

## RipsawEngine::Game

### Member Variables

- `class Engine*` `mEngine`: Pointer to main Engine instance.

### Member Functions

#### `RipsawEngine::Game::Game`

Default constructor for Game .

The philosophy as of now for the engine is, engine code and game code must have a clear line between them. Engine would act as an operating system for game, maintaining all low level subsystems and calculations. Engine would have no idea about what a game is. It would just run the main loop which would update and render all necessary systems. As the engine's update and render code would be locked down, it would be impossible to design and inject custom update code to entities. This class acts as a solution to that. It exposes some virtual API which can be extended in sandbox code to inject custom entity behavior in the engine. Game is instantiated in sandbox, then Engine receives a pointer to Game instance. Engine internally calls Game 's virtual APIs in appropriate places which enables integration of custom entity behavior without touching engine code. Game also needs access to Engine instance which it receives in Engine 's internal implementation via the setEngine() method.

#### `void RipsawEngine::Game::setEngine`

Sets mEngine with pointer to Engine instance.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `engine` | `class Engine *` | Pointer to Engine instance. |

#### `void RipsawEngine::Game::initGame`

Custom initialization logic for Game .

#### `void RipsawEngine::Game::updateGame`

Custom update logic for Game .

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `dt` | `double` | Delta-time. |

#### `void RipsawEngine::Game::renderGame`

Custom render logic for Game .


---


<!-- AUTODOC:END -->
</details>

# Note

- There is absolutely zero tolerance for any AI generated code in `engine/`. If you want to contribute in the engine, write everything by yourself. `sandbox/` is for testing engine features. You can test in any way you want but no AI generated code in `sandbox/` would be pushed into the main branch. On the other hand, scripts in `scripts/` are just helper scripts unrelated to engine. So, as long as the functionality works properly, anything is acceptable. For example, `scripts/gen_docs.py` is completely AI generated whose functionality is to parse documentation from engine codebase and automatically generate [README.md](README.md).

- All methods and variables in engine must be properly documented abiding by doxygen documentation rules.

# License

Copyright © 2026  Hossain Md. Fahim  <hossainmdfahim66@gmail.com>  
See [LICENSE](./LICENSE.md) for more information.

