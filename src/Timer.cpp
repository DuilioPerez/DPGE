// File: Timer.cpp
// Author: Duilio Pérez
// Implementation of Timer class.
#include "Timer.hpp"
using namespace DPGE;

// Pause the timer.
void Timer::pause()
{
  if (!this->isPaused)
  {
    this->isPaused  = true;
    this->startTime = SDL_GetTicks64() - this->startTime;
  }
}

// Unpause the timer.
void Timer::unpause()
{
  if (this->isPaused)
  {
    this->isPaused  = false;
    this->startTime = SDL_GetTicks64() - this->startTime;
  }
}

// Restart the timer.
Uint64 Timer::restart()
{
  // The value to return.
  Uint64 elapsedTime = this->getMiliseconds();
  // Restart the timer.
  this->isPaused  = false;
  this->startTime = SDL_GetTicks64();
  // Return the time.
  return elapsedTime;
}

// Get the elapsed seconds.
double Timer::getSeconds()
{
  if (this->isPaused)
    return this->startTime / 1000.0;
  return (SDL_GetTicks64() - this->startTime) / 1000.0;
}

// Get the miliseconds.
Uint64 Timer::getMiliseconds()
{
  if (this->isPaused)
    return this->startTime;
  return SDL_GetTicks64() - this->startTime;
}
