# RipsawEngine

2D/3D game engine implemented from scratch in C++.

# API Documentation

<!-- AUTODOC:BEGIN -->

## RipsawEngine::Actor

### Member Variables

- `class Engine*` `mEngine`: Main engine instance.
- `std::vector<class Component*>` `mComponents`: Vector of all components tied to the actor.
- `class TransformComponent*` `mTransformComponent`: TransformComponent tied to the actor (if any).
- `size_t` `mTotalComponentSize`: Total size of all components held by actor.

### Member Functions

#### `RipsawEngine::Actor::Actor`

Constructs actor with pointer to Engine instance.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `engine` | `class Engine *` | Pointer to Engine instance. |

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

Adds component to actor storing in mComponents.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `component` | `class Component *` | Component to be added to actor. |

#### `void RipsawEngine::Actor::removeComponent`

Removes component from actor.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `component` | `class Component *` | Component to be removed from actor. |

#### `TransformComponent * RipsawEngine::Actor::getTransformComponent`

Returns mTransformComponent.

This method works as a way for other components to get access to TransformComponent.

#### `void RipsawEngine::Actor::setTransformComponent`

Sets mTransformComponent.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `tc` | `class TransformComponent *` | Transform component. |

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


---

## RipsawEngine::Component

### Member Variables

- `class Actor*` `mOwner`: Pointer to actor owning the component.

### Member Functions

#### `RipsawEngine::Component::Component`

Constructs component with pointer to Actor instance.

This is an abstract base class for defining components. All derived components must implement isComponentValid(). This provides a way for instantiated component to mark themselves valid or invalid based on certain conditions. If a derived component is surely a valid component, then isComponentValid() should just return True.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor *` | Actor owning the component. |

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
- `std::pair<float, float>` `mTexSize`: Texture size.
- `float` `mScale`: Texture scale.

### Member Functions

#### `RipsawEngine::SpriteComponent::SpriteComponent`

Constructs sprite component with owning actor, renderer, and image file.

Constructs transform component with owning actor, position, and velocity.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor *` | Actor owning the component. |
| `renderer` | `SDL_Renderer *` | Renderer. |
| `imgfile` | `const std::string &` | Path to image file. |

#### `RipsawEngine::SpriteComponent::~SpriteComponent`

Destructs SpriteComponent.

#### `bool RipsawEngine::SpriteComponent::isComponentValid`

Checks if SpriteComponent is valid.

#### `SDL_Texture * RipsawEngine::SpriteComponent::getTexture`

Returns mTexture.

#### `std::pair< int, int > RipsawEngine::SpriteComponent::getTexSize`

Returns texture size.

#### `void RipsawEngine::SpriteComponent::draw`

Draws texture on window.

#### `float RipsawEngine::SpriteComponent::getScale`

Returns scale of texture.

#### `void RipsawEngine::SpriteComponent::setScale`

Sets scale of texture.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `scale` | `float` | Texture scale. |


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
- `Uint64` `mTicksCount`: Ticks passed since last frame.
- `double` `mtimer`: Timer denoting if 1 second has passed.
- `int` `mFrames`: Frames per second.
- `std::vector<class Actor*>` `mActors`: List of all actors.
- `std::vector<class SpriteComponent*>` `mSprites`: List of all sprites to be drawn.
- `size_t` `mTotalActorsSize`: Total size of all registered actors.

### Member Functions

#### `RipsawEngine::Engine::Engine`

Constructs engine with configurable window name and size.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `wname` | `const std::string &` | Custom window name. |
| `w` | `int` | Custom window width. |
| `h` | `int` | Custom window height. |

#### `RipsawEngine::Engine::~Engine`

Destructs engine.

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

#### `void RipsawEngine::Engine::addActor`

Adds actor to mActors.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor *` | Pointer to Actor instance. |

#### `void RipsawEngine::Engine::removeActor`

Removes actor from mActors.

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

#### `void RipsawEngine::Engine::processInput`

Processes inputs.

#### `void RipsawEngine::Engine::updateEngine`

Updates the game world.

#### `void RipsawEngine::Engine::renderEngine`

Renders game output on screen.


---


<!-- AUTODOC:END -->

