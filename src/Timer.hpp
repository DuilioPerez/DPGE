/// @file Timer.hpp
/// @author Duilio Pérez
/// @brief Class to work with timers.
#ifndef TIMER_HPP
#define TIMER_HPP true
#include <SDL2/SDL.h>

namespace DPGE
{

  /// @brief The Timer class.
  class Timer final
  {
  public:
    /// @brief Pause the timer.
    void pause();
    /// @brief Unpause the timer.
    void unpause();
    /// @brief Restart the timer.
    /// @return The elapsed time as miliseconds.
    Uint64 restart();
    /// @brief Get the elapsed seconds.
    double getSeconds();
    /// @brief Get the elapsed miliseconds.
    Uint64 getMiliseconds();

  private:
    /// @brief Indicator to know if the timer is paused.
    bool isPaused = false;
    /// @brief The start time of the timer.
    Uint64 startTime = SDL_GetTicks64();
  };

} // namespace DPGE

#endif
