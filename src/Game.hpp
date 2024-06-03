/// @file Game.hpp
/// @author Duilio Pérez
/// @brief Class to work with the game.
#ifndef GAME_HPP
#define GAME_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/// @brief Game engine's namespace.
///
/// This namespace contains all the classes and functions
/// needed by the game.
namespace DPGE
{

  /// @brief The class to work with the game.
  ///
  /// This class contains all the functions needed for the
  /// mainloop of a game. It is optimal for 2D games. It has
  /// support for emscripten.
  class Game final
  {
  public:
    /// @brief Deleted copy constructor.
    Game(const Game &) = delete;
    /// @brief Initialize the game.
    void initialize();
    /// @brief Run the game.
    void run();
    /// @brief Query if the game is running.
    bool isRunning();
    /// @brief Deinitialize the game.
    void deinitialize();
    /// @brief Query if the audio plugin was init.
    bool hasAudio();
    /// @brief Make a request to exit.
    void exit();
    /// @brief Get the game's window.
    SDL_Window *getWindow();
    /// @brief Get the game's renderer.
    SDL_Renderer *getRenderer();
    /// @brief Get the instance of the game.
    static Game &getInstace();
    /// @brief Copy operator deleted.
    const Game &operator=(const Game &) = delete;

  private:
    /// @brief Private default constructor.
    Game() = default;
    /// @brief Flag to know if the image plugin was init.
    bool imagePluginWasInit = false;
    /// @brief Flag to know if the font plugin was init.
    bool ttfPluginWasInit = false;
    /// @brief Flag to know if the audio plugin was init.
    bool audioPluginWasInit = false;
    /// @brief Game's window.
    SDL_Window *window = nullptr;
    /// @brief Game's renderer.
    SDL_Renderer *renderer = nullptr;
    /// @brief Bit indicator to know if the game is running.
    bool isGameRunning = false;
  };

  /// @brief The properties of the current game.
  extern struct GameProperties
  {
    /// @brief SDL2's initialization flags.
    Uint32 initializationFlags;
    /// @brief Image's support bit indicator.
    bool imagePluginSupport;
    /// @brief Image flags.
    IMG_InitFlags imagePluginFlags;
    /// @brief TTF support bit indicator.
    bool ttfPluginSupport;
    /// @brief Audio support bit indicator.
    bool audioPluginSupport;
    /// @brief Audio frequency.
    int audioPluginFrequency;
    /// @brief The formats supported by the audio plugin.
    Uint16 audioPluginFormats;
    /// @brief Audio channels.
    Uint16 audioPluginChannels;
    /// @brief Audio buffer size in sample FRAMES (total
    /// samples divided by channel count).
    int audioPluginChunkSize;
    /// @brief Game's window title.
    const char *windowTitle;
    /// @brief Game's x window position.
    int x;
    /// @brief Game's y window position.
    int y;
    /// @brief Game's window width.
    int width;
    /// @brief Game's window height.
    int height;
    /// @brief Game's window flags.
    SDL_WindowFlags windowFlags;
    /// @brief Renderer index.
    int rendererIndex;
    /// @brief Renderer flags.
    SDL_RendererFlags rendererFlags;
  } gameProperties;

  /// @brief The instace of the class Game.
  extern Game &theGame;

} // namespace DPGE

#endif
