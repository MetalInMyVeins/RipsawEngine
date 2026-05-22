#include "RipsawEngine/2D/Core/Game.hxx"
#include "RipsawEngine/2D/Core/Engine.hxx"

namespace RipsawEngine
{

void Game::setEngine(Engine* engine)
{
  mEngine = engine;
}

void Game::initGame()
{}

void Game::updateGame([[maybe_unused]] double dt)
{}

void Game::renderGame()
{}

}

