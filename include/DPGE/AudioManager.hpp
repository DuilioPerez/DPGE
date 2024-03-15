/// @file AudioManager.hpp
/// @author Duilio Pérez
/// @brief The game's audio manager.
#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP true
#include <SDL2/SDL_mixer.h>
#include <ctime>
#include <map>
#include <random>
#include <string>
#include <vector>

namespace DPGE
{

  /// @brief The game's audio manager.
  class AudioManager final
  {
  public:
    /// @brief Copy constructor deleted.
    AudioManager(const AudioManager &) = delete;
    /// @brief Read an audio from a file.
    /// @param name The audio's id.
    /// @param file The audio's path file.
    /// @return true in success.
    ///
    /// The audio is being reading from a stream. If that
    /// stream is closed, it can caused an error. Use this
    /// to read audio directly from a stream, for example,
    /// it's recommended for music or large files to don't
    /// use much RAM.
    bool loadMusic(
      const std::string &name, const std::string &file);
    /// @brief Load an audio from a file.
    /// @param name The name of the audio.
    /// @param file The audio's path file.
    /// @return true in success.
    ///
    /// The audio is stored in RAM, so use it for short
    /// sounds, like sound effects.
    bool loadSound(
      const std::string &name, const std::string &file);
    /// @brief Play a music if is not playing, or select one
    /// randomly.
    /// @param name The name of the music to play.
    void playMusic(const std::string &name);
    void playMusic();
    /// @brief Play a sound stored in RAM.
    /// @param name The sound's name.
    void playSound(const std::string &name);
    /// @brief Erase an audio stream.
    /// @param name The audio's name.
    void eraseMusic(const std::string &name);
    /// @brief Erase a sound from RAM.
    /// @param name The sound's name.
    void eraseSound(const std::string &name);
    /// @brief Erase all the audios in the manager.
    void clear();
    /// @brief Get the class' instace.
    static AudioManager &getInstance();
    /// @brief Copy operator deleted.
    const AudioManager &operator=(
      const AudioManager &) = delete;

  private:
    /// @brief Private default constructor.
    AudioManager() = default;
    /// @brief The names of all the music to random playing.
    std::vector<std::string> musicNames;
    /// @brief The musics to play.
    std::map<std::string, Mix_Music *> music;
    /// @brief The game's sound effects.
    std::map<std::string, Mix_Chunk *> soundEffects;
    /// @brief Random numbers engine.
    std::default_random_engine engine{
      static_cast<unsigned>(time(nullptr))};
    /// @brief Number distribution.
    std::uniform_int_distribution<size_t> distribution;
  };

  /// @brief The reference to the audio manager.
  extern AudioManager &theAudioManager;

} // namespace DPGE

#endif
