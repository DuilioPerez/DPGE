// File: AudioManager.cpp
// Author: Duilio Pérez
// Implementation of the audio manager.
#include "AudioManager.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <algorithm>
#include <ctime>
#include <string>
using namespace DPGE;
using namespace std;

AudioManager &DPGE::theAudioManager =
  AudioManager::getInstance();

// Load a music from a stream.
bool AudioManager::loadMusic(
  const string &name, const string &file)
{
  // Try to load the music.
  if (!(this->music[name] = Mix_LoadMUS(file.c_str())))
  {
    // Print an error message.
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error loading a music: %s.\n", Mix_GetError());
    // Delete the element from its map.
    this->music.erase(name);
    return false;
  }
  // Add the name to the class' vector.
  this->musicNames.push_back(name);
  // Set the number distribution.
  if (!this->music.empty())
    this->distribution = uniform_int_distribution<size_t>(
      1, this->music.size());
  return true;
}

// Load a sound effect.
bool AudioManager::loadSound(
  const string &name, const string &file)
{
  // Try to load the music.
  if (!(this->soundEffects[name] =
          Mix_LoadWAV(file.c_str())))
  {
    // Prints an error message.
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error loading a sound in RAM: %s.\n",
      Mix_GetError());
    // Erase the element from its map.
    this->soundEffects.erase(name);
    return false;
  }
  return true;
}

// Play a music.
void AudioManager::playMusic(const string &name)
{
  // Play the music if is not playing.
  if (!Mix_PlayingMusic())
    if (!this->music.empty())
      // Play the music if is in its map.
      if (this->music.find(name) != this->music.cend())
        if (Mix_PlayMusic(this->music[name], 0) < 0)
          SDL_LogError(SDL_LOG_CATEGORY_ERROR,
            "Error playing a music: %s.\n", Mix_GetError());
}

// Play a random music.
void AudioManager::playMusic()
{
  // The index to the music to play.
  size_t musicIndex = this->distribution(this->engine);
  // If the index is out of range.
  if (musicIndex >= this->musicNames.size())
    // Make the index in the right range.
    musicIndex = this->musicNames.size() - musicIndex;
  // Play a random music if is not playing.
  if (!Mix_PlayingMusic())
    if (!this->music.empty())
      if (Mix_PlayMusic(
            this->music[this->musicNames[musicIndex]], 0) <
          0)
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
          "Error playing a music: %s.\n", Mix_GetError());
}

// Play a sound.
void AudioManager::playSound(const string &name)
{
  // Play the sound if is in its map.
  if (this->soundEffects.find(name) !=
      this->soundEffects.cend())
    if (!this->soundEffects.empty())
      if (Mix_PlayChannel(-1, this->soundEffects[name], 0) <
          0)
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
          "Error playing a sound effect: %s.\n",
          Mix_GetError());
}

// Erase a music.
void AudioManager::eraseMusic(const std::string &name)
{
  auto it = this->music.find(name);
  if (it != this->music.end())
  {
    // Free the music
    Mix_FreeMusic(it->second);
    // Erase it from the map.
    this->music.erase(it);
    auto element = std::find(this->musicNames.begin(),
      this->musicNames.end(), name);
    if (element != this->musicNames.end())
      // Erase the element.
      this->musicNames.erase(element);
    // Set the new max random generated number.
    if (!this->music.empty())
    {
      this->distribution =
        std::uniform_int_distribution<size_t>(
          0, this->music.size() - 1);
    }
  }
}

// Erase a sound effect.
void AudioManager::eraseSound(const string &name)
{
  // Delete the sound effect if is found.
  if (this->soundEffects.find(name) !=
      this->soundEffects.cend())
    Mix_FreeChunk(this->soundEffects[name]);
  // Delete its reference.
  this->soundEffects.erase(name);
}

// Clear all the music and sounds.
void AudioManager::clear()
{
  // Free all the sound effects.
  for (auto &i : this->soundEffects)
    Mix_FreeChunk(i.second);
  // Delete all the references to the sound effects.
  this->soundEffects.clear();
  // Free all the music.
  for (auto &i : this->music)
    Mix_FreeMusic(i.second);
  // Clear the music's map and vector.
  this->music.clear();
  this->musicNames.clear();
}

// Get the class' instance.
AudioManager &AudioManager::getInstance()
{
  static AudioManager theInstance;
  return theInstance;
}
