# RipsawEngine

2D/3D game engine implemented from scratch in C++.

# API Documentation

## RipsawEngine::Actor

### Member Variables

- `class Engine*`  `mEngine`: Main engine instance.
- `std::vector<class Component*>`  `mComponents`: Vector of all components tied to the actor.
- `class TransformComponent*`  `mTransformComponent`: TransformComponent tied to the actor (if any).

### Member Functions

#### `RipsawEngine::Actor::Actor`

Constructs actor with pointer to Engine instance.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `engine` | `class Engine *` | Pointer to Engine instance. |

#### `RipsawEngine::Actor::~Actor`

Destructor.

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

Remove component from actor.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `component` | `class Component *` | Component to be removed from actor. |

#### `TransformComponent * RipsawEngine::Actor::getTransformComponent`

Returns mTransformComponent.

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


---

## RipsawEngine::Component

### Member Variables

- `class Actor*`  `mOwner`: Pointer to actor owning the component.

### Member Functions

#### `RipsawEngine::Component::Component`

Constructs component with pointer to Actor instance.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor *` | Actor owning the component. |

#### `RipsawEngine::Component::~Component`

Destructor.

#### `void RipsawEngine::Component::update`

Updates component.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `dt` | `double` | Delta-time. |


---

## RipsawEngine::TransformComponent

### Member Variables

- `glm::vec2`  `mPos`: Position.
- `glm::vec2`  `mVel`: Velocity.

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

Destructor.

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

- `int`  `mScreenWidth`: Screen width.
- `int`  `mScreenHeight`: Screen height.
- `bool`  `mIsDisplaySetManually`: True if screen size has been manually configured.
- `bool`  `mIsRunning`: True if game loop is running.
- `SDL_Window*`  `mWindow`: Window pointer.
- `SDL_Renderer*`  `mRenderer`: Renderer pointer.
- `Uint64`  `mTicksCount`: Ticks passed since last frame.
- `double`  `mtimer`: Timer denoting if 1 second has passed.
- `int`  `mFrames`: Frames per second.
- `std::vector<class Actor*>`  `mActors`: List of all actors.

### Member Functions

#### `RipsawEngine::Engine::Engine`

Constructs engine with configurable window size.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `w` | `int` | Custom window width |
| `h` | `int` | Custom window height |

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

#### `void RipsawEngine::Engine::processInput`

Processes inputs.

#### `void RipsawEngine::Engine::updateEngine`

Updates the game world.

#### `void RipsawEngine::Engine::renderEngine`

Renders game output on screen.


---



