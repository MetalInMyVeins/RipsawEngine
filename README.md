# RipsawEngine

2D/3D game engine implemented from scratch in C++.

# API Documentation

<!-- AUTODOC:BEGIN -->

## Engine

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

#### `Engine::Engine`

Constructs engine with configurable window size.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `w` | `int` | Custom window width |
| `h` | `int` | Custom window height |

#### `bool Engine::init`

Initializes video, audio, window, renderer etc.

#### Return

| Type | Description |
|--------|-------------|
| bool | True if successful, False otherwise. |

#### `void Engine::run`

Runs the main game loop.

#### `void Engine::shutdown`

Frees resources and prepares for program shutdown.

#### `void Engine::addActor`

Adds actor to mActors.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor *` | Pointer to Actor instance. |

#### `void Engine::removeActor`

Removes actor from mActors.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor *` | Pointer to Actor instance. |

#### `void Engine::processInput`

Processes inputs.

#### `void Engine::updateEngine`

Updates the game world.

#### `void Engine::renderEngine`

Renders game output on screen.

#### `bool Engine::loadMedia`

Loads game assets.

#### `void Engine::unloadMedia`

Unloads game assets.


---

## Actor

### Member Variables

- `class Engine*`  `mEngine`: Main engine instance.
- `std::vector<class Component*>`  `mComponents`: Vector of all components tied to the actor.
- `class TransformComponent*`  `mTransformComponent`: TransformComponent tied to the actor (if any).

### Member Functions

#### `Actor::Actor`

Constructs actor with pointer to Engine instance.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `engine` | `class Engine *` | Pointer to Engine instance. |

#### `Actor::~Actor`

Destructor.

#### `void Actor::update`

Updates actor.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `dt` | `double` | Delta-time. |

#### `void Actor::updateComponents`

Updates all components tied to the actor.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `dt` | `double` | Delta-time. |

#### `void Actor::addComponent`

Adds component to actor storing in mComponents.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `component` | `class Component *` | Component to be added to actor. |

#### `void Actor::removeComponent`

Remove component from actor.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `component` | `class Component *` | Component to be removed from actor. |

#### `TransformComponent * Actor::getTransformComponent`

Returns mTransformComponent.

#### `void Actor::setTransformComponent`

Sets mTransformComponent.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `tc` | `class TransformComponent *` | Transform component. |

#### `glm::vec2 Actor::getPosition`

Returns position of actor.

#### `void Actor::setPosition`

Sets position of actor.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `pos` | `const glm::vec2 &` | Position of actor. |

#### `glm::vec2 Actor::getVelocity`

Sets velocity of actor.

#### `void Actor::setVelocity`

Sets velocity of actor.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `vel` | `const glm::vec2 &` | Velocity of actor. |


---

## Component

### Member Variables

- `class Actor*`  `mOwner`: Pointer to actor owning the component.

### Member Functions

#### `Component::Component`

Constructs component with pointer to Actor instance.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor *` | Actor owning the component. |

#### `Component::~Component`

Destructor.

#### `void Component::update`

Updates component.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `dt` | `double` | Delta-time. |


---

## TransformComponent

### Member Variables

- `glm::vec2`  `mPos`: Position.
- `glm::vec2`  `mVel`: Velocity.

### Member Functions

#### `TransformComponent::TransformComponent`

Constructs transform component with owning actor, position, and velocity.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `actor` | `class Actor *` | Owning actor of transform component. |
| `pos` | `const glm::vec2 &` | Position of actor. |
| `vel` | `const glm::vec2 &` | Velocity of actor. |

#### `TransformComponent::~TransformComponent`

Destructor.

#### `void TransformComponent::update`

Updates transform component.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `dt` | `double` | Delta-time. |

#### `glm::vec2 TransformComponent::getPosition`

Returns position.

#### `void TransformComponent::setPosition`

Sets position.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `pos` | `const glm::vec2 &` | Position. |

#### `glm::vec2 TransformComponent::getVelocity`

Returns velocity.

#### `void TransformComponent::setVelocity`

Sets velocity.

#### Parameters

| Name | Type | Description |
|------|------|-------------|
| `vel` | `const glm::vec2 &` | Velocity. |


---


<!-- AUTODOC:END -->

