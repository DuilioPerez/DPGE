// File: Game.cpp
// Author: Duilio Pérez.
// Implementation of class Game.
#include "Game.hpp"
#include "AudioManager.hpp"
#include "GameStateManager.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
using namespace DPGE;

// Default game's configuration.
DPGE::GameProperties DPGE::gameProperties = {
  SDL_INIT_AUDIO | SDL_INIT_VIDEO, true, IMG_INIT_PNG, true,
  true, MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
  MIX_DEFAULT_CHANNELS, 2048, "DPGE",
  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360,
  SDL_WINDOW_SHOWN, -1, SDL_RENDERER_ACCELERATED};

// Initialize the reference to the game's instance.
Game &DPGE::theGame = Game::getInstace();

#ifdef __EMSCRIPTEN__

// Protopype for the game loop for emscripten.
static void emscriptenMainLoop();

// Function's definition.
static void emscriptenMainLoop()
{
  // If the game isn't running, deinitialize it.
  if (!theGame.isRunning)
  {
    theGame.deinitialize();
    emscripten_cancel_main_loop();
  }
  // Regular functions.
  theGameStateManager.handleEvents();
  theGameStateManager.update();
  theGameStateManager.render();
}

#endif

// Initialize the game.
void Game::initialize()
{
  // Initialize SDL2.
  if (SDL_Init(gameProperties.initializationFlags) < 0)
  {
    // Show a message box.
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error initializing SDL2", SDL_GetError(), nullptr);
    // Print an error message.
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error initializing SDL2: %s.\n", SDL_GetError());
    return;
  }
  // Create the game's renderer.
  this->window = SDL_CreateWindow(
    gameProperties.windowTitle, gameProperties.x,
    gameProperties.y, gameProperties.width,
    gameProperties.height, gameProperties.windowFlags);
  if (!this->window)
  {
    // Show a message error.
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error creating the game's renderer", SDL_GetError(),
      nullptr);
    // Print an error message.
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error creating the game's window: %s.\n",
      SDL_GetError());
    return;
  }
  // Create the game's renderer.
  this->renderer = SDL_CreateRenderer(this->window,
    gameProperties.rendererIndex,
    gameProperties.rendererFlags);
  if (!this->renderer)
  {
    // Show a message box.
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error creating the game's renderer", SDL_GetError(),
      this->window);
    // Print a message error.
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error creating the game's renderer: %s.\n",
      SDL_GetError());
    return;
  }
  // Initialize SDL2_image if is requested.
  if (gameProperties.imagePluginSupport)
  {
    if (!(IMG_Init(gameProperties.imagePluginFlags) &
          gameProperties.imagePluginFlags))
    {
      // Show a message box.
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
        "Error initializing SDL2_image", IMG_GetError(),
        this->window);
      // Print an message error.
      SDL_LogError(SDL_LOG_CATEGORY_ERROR,
        "Error initializing SDL2_image: %s.\n",
        IMG_GetError());
      return;
    }
    else
      this->imagePluginWasInit = true;
  }
  // Initialize SDL2_ttf if is requested.
  if (gameProperties.ttfPluginSupport)
  {
    if (TTF_Init() < 0)
    {
      // Show a message box.
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
        "Error initializing SDL2_ttf", TTF_GetError(),
        this->window);
      // Print an message error.
      SDL_LogError(SDL_LOG_CATEGORY_ERROR,
        "Error initializing SDL2_ttf: %s.\n",
        TTF_GetError());
      return;
    }
    else
      this->ttfPluginWasInit = true;
  }
  // Initialize SDL2_mixer if is requested.
  if (gameProperties.audioPluginSupport)
  {
    if (Mix_OpenAudio(gameProperties.audioPluginFrequency,
          gameProperties.audioPluginFormats,
          gameProperties.audioPluginChannels,
          gameProperties.audioPluginChunkSize) < 0)
      // Print an warning message.
      SDL_LogWarn(SDL_LOG_CATEGORY_ERROR,
        "Error initializing SDL2_mixer: %s.\n",
        Mix_GetError());
    else
      this->audioPluginWasInit = true;
  }
  // Set initialization flag to true.
  this->isGameRunning = true;
}

// Run the game.
void Game::run()
{
#ifdef __EMSCRIPTEN__
  // Call the emscripten main loop function.
  emscripten_set_main_loop(emscriptenMainLoop, 0, 1);
#else
  // Normal game loop.
  while (this->isRunning())
  {
    theGameStateManager.handleEvents();
    theGameStateManager.update();
    theGameStateManager.render();
  }
#endif
}

// Query if the game is running.
bool Game::isRunning()
{
  return this->isGameRunning;
}

// Deinitialize the game.
void Game::deinitialize()
{
  // Clear the audio manager.
  theAudioManager.clear();
  // Set the game state to nullptr to delete all if there
  // are in the stack.
  theGameStateManager.setGameState(nullptr);
  // Shut down SDL2_mixer.
  if (this->audioPluginWasInit)
  {
    Mix_Quit();
    this->audioPluginWasInit = false;
  }
  // Shut down SDL2_ttf.
  if (this->ttfPluginWasInit)
  {
    TTF_Quit();
    this->ttfPluginWasInit = false;
  }
  // Destroy the renderer.
  if (this->renderer)
  {
    SDL_DestroyRenderer(this->renderer);
    this->renderer = nullptr;
  }
  // Destroy the window.
  if (this->window)
  {
    SDL_DestroyWindow(this->window);
    this->window = nullptr;
  }
  // Shut down SDL2.
  if (SDL_WasInit(0) & gameProperties.initializationFlags)
    SDL_Quit();
  SDL_Log("Game deinitialized!");
}

// Query if the game has audio support.
bool Game::hasAudio()
{
  return this->audioPluginWasInit;
}

// Make a request to exit.
void Game::exit()
{
  this->isGameRunning = false;
}

// Get the game's window.
SDL_Window *Game::getWindow()
{
  return this->window;
}

// Get the game's renderer.
SDL_Renderer *Game::getRenderer()
{
  return this->renderer;
}

// Get the class' instance.
Game &Game::getInstace()
{
  static Game theInstance;
  return theInstance;
}
