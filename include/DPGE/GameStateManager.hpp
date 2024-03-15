/// @file GameStateManager.hpp
/// @author Duilio Pérez
/// @brief The game state class.
#ifndef GAMESTATEMANAGER_HPP
#define GAMESTATEMANAGER_HPP true
#include "GameState.hpp"
#include <SDL2/SDL.h>
#include <stack>

namespace DPGE
{

  /// @brief The game state manager.
  class GameStateManager final
  {
  public:
    /// @brief Copy constructor deleted.
    GameStateManager(const GameStateManager &) = delete;
    /// @brief Set a new game state.
    /// @param gameState The game state to register, nullptr
    /// to exit.
    void setGameState(GameState *gameState);
    /// @brief Push a game state over the current.
    /// @param gameState The game state to push, nullptr
    /// doesn't have effect.
    void pushGameState(GameState *gameState);
    /// @brief Pop a game state and delete it.
    ///
    /// If there is only one game state in the game state
    /// stack, it will exit from the game.
    void popGameState();
    /// @brief Handle the events of the current game state.
    void handleEvents();
    /// @brief Update the current game state.
    void update();
    /// @brief Show the scene to render.
    void render();
    /// @brief Get the instace of the game state manager.
    static GameStateManager &getInstace();
    /// @brief Copy operator deleted.
    const GameStateManager &operator=(
      const GameStateManager &) = delete;

  private:
    /// @brief Default private constructor.
    GameStateManager() = default;
    /// @brief The game states.
    std::stack<GameState *> gameStates;
    /// @brief The current event in the top of the queue.
    SDL_Event topEvent;
  };

  /// @brief Reference to the game state manager.
  extern GameStateManager &theGameStateManager;

} // namespace DPGE

#endif
