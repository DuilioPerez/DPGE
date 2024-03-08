/// @file GameState.hpp
/// @author Duilio Pérez
/// @brief The base class for every game state.
#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP true
#include <SDL2/SDL.h>

namespace DPGE
{

  /// @brief The base class for every game state.
  class GameState
  {
  public:
    /// @brief Handle the game's events.
    /// @param evenr The next event to handle.
    virtual void handleEvents(const SDL_Event &event) = 0;
    /// @brief Update the current game state.
    virtual void update() = 0;
    /// @brief Show the scene to render.
    virtual void render() = 0;
    /// @brief Virtual destructor.
    virtual ~GameState(){};
  };

} // namespace DPGE

#endif
