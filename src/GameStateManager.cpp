/// @file GameStateManager.cpp
/// @authlr Duilio Pérez
/// @brief Game state manager's implementation.
#include "GameStateManager.hpp"
#include "Game.hpp"
#include "GameState.hpp"
using namespace DPGE;

// Define the reference to the game state manager.
GameStateManager &DPGE::theGameStateManager =
  GameStateManager::getInstace();

// Set the current game state.
void GameStateManager::setGameState(GameState *gameState)
{
  // Delete all the game states.
  while (!this->gameStates.empty())
  {
    delete this->gameStates.top();
    this->gameStates.pop();
  }
  // If the game state is nullptr, exit from the game.
  if (!gameState)
    theGame.exit();
  // Otherwise, set the current game state.
  else
    this->gameStates.push(gameState);
}

// Push a game state.
void GameStateManager::pushGameState(GameState *gameState)
{
  // Push the game state if is not nullptr.
  if (gameState)
    this->gameStates.push(gameState);
}

// Pop a game state.
void GameStateManager::popGameState()
{
  // If the game state's stack isn't empty, pop the game
  // state in its top.
  if (!this->gameStates.empty())
  {
    delete this->gameStates.top();
    this->gameStates.pop();
  }
  // If now the game state's stack is empty, exit from the
  // game.
  if (this->gameStates.empty())
    theGame.exit();
}

// Handle the events of a game state.
void GameStateManager::handleEvents()
{
  // Handle the events while they're happenning.
  while (SDL_PollEvent(&this->topEvent))
    // If there is no game state, send a request to quit.
    if (this->gameStates.empty())
      theGame.exit();
  // If the game is running and there is at least one game
  // state, it handle the events.
  if (theGame.isRunning() && !this->gameStates.empty())
    this->gameStates.top()->handleEvents(this->topEvent);
}

// Update the current game state.
void GameStateManager::update()
{
  // The same that handleEvents function.
  if (theGame.isRunning() && !this->gameStates.empty())
    this->gameStates.top()->update();
}

// Render the current game state.
void GameStateManager::render()
{
  // The same that update function, but verify if the window
  // is being shown
  if (theGame.isRunning() && !this->gameStates.empty() &&
      (SDL_GetWindowFlags(theGame.getWindow()) &
        SDL_WINDOW_SHOWN))
    this->gameStates.top()->render();
}

// Get the class instance.
GameStateManager &GameStateManager::getInstace()
{
  static GameStateManager theInstance;
  return theInstance;
}
