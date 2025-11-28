#include "RipsawEngine/Core/Game.hxx"
#include "RipsawEngine/Core/Engine.hxx"

namespace RipsawEngine
{

void Game::setEngine(Engine* engine)
{
  mEngine = engine;
}

void Game::initGame()
{}

void Game::updateGame(double dt)
{}

void Game::renderGame()
{}

}

