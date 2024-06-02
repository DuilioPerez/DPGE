// File: TextureManager.cpp
// Author: Duilio Pérez
// Implementation of the texture manager.
#include "TextureManager.hpp"
#include "Game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
using namespace DPGE;
using namespace std;

// Define the instance of the texture manager.
TextureManager &DPGE::theTextureManager =
  TextureManager::getInstance();

// Load the font to render text.
bool TextureManager::openFont(const string &path, int size)
{
  // Close the current font if there is one.
  if (this->font)
  {
    TTF_CloseFont(this->font);
    this->font = nullptr;
  }
  // Load the font.
  this->font = TTF_OpenFont(path.c_str(), size);
  if (!this->font)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Can't load the game's font", TTF_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Can't load the game's font: %s.\n", TTF_GetError());
    return false;
  }
  return true;
}

// Load a texture from a file.
bool TextureManager::loadFromFile(
  const string &name, const string &path)
{
  // The texture to loadx
  SDL_Texture *textureToLoad = nullptr;
  // If the texture exists, don't load.
  if (this->textures.find(name) != this->textures.end())
    return false;
  textureToLoad =
    IMG_LoadTexture(theGame.getRenderer(), path.c_str());
  if (!textureToLoad)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error loading a texture", IMG_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error loading a texture: %s.\n", IMG_GetError());
    return false;
  }
  this->textures[name] = textureToLoad;
  return true;
}

// Create and save a texture from a text.
bool TextureManager::loadFromText(
  const string &name, const string &text)
{
  // Hold the text temporary.
  SDL_Surface *loadedText = nullptr;
  // The text converted into texture.
  SDL_Texture *convertedText = nullptr;
  // If the texture exists, don't create a new one.
  if (this->textures.find(name) != this->textures.end())
    return false;
  // Load the text.
  switch (this->textRenderingQuality)
  {
  case TextQuality::BLENDED:
    loadedText = TTF_RenderUTF8_Blended(
      this->font, text.c_str(), this->getForegroundColor());
    break;
  case TextQuality::LCD:
    loadedText = TTF_RenderUTF8_LCD(this->font,
      text.c_str(), this->getForegroundColor(),
      this->getBackgroundColor());
    break;
  case TextQuality::SHADED:
    loadedText = TTF_RenderUTF8_Shaded(this->font,
      text.c_str(), this->getForegroundColor(),
      this->getBackgroundColor());
    break;
  case TextQuality::SOLID:
    loadedText = TTF_RenderUTF8_Solid(
      this->font, text.c_str(), this->getForegroundColor());
    break;
  }
  if (!loadedText)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error rendering a text", TTF_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error rendering a text: %s.\n", TTF_GetError());
    return false;
  }
  // Convert to texture.
  convertedText = SDL_CreateTextureFromSurface(
    theGame.getRenderer(), loadedText);
  // Free the surfacec
  SDL_FreeSurface(loadedText);
  // If the texture wasn't created, return false.
  if (!convertedText)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error creating a texture", SDL_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error creating a texture: %s.\n", SDL_GetError());
    return false;
  }
  this->textures[name] = convertedText;
  return true;
}

// Load a texture from a wrapped text.
bool TextureManager::loadFromText(
  const string &name, const string &text, Uint32 width)
{
  // Hold the text temporary.
  SDL_Surface *loadedText = nullptr;
  // The text converted into texture.
  SDL_Texture *convertedText = nullptr;
  // If the texture exists, don't load.
  if (this->textures.find(name) != this->textures.end())
    return false;
  // Load the text.
  switch (this->textRenderingQuality)
  {
  case TextQuality::BLENDED:
    loadedText = TTF_RenderUTF8_Blended_Wrapped(this->font,
      text.c_str(), this->getForegroundColor(), width);
    break;
  case TextQuality::LCD:
    loadedText = TTF_RenderUTF8_LCD_Wrapped(this->font,
      text.c_str(), this->getForegroundColor(),
      this->getBackgroundColor(), width);
    break;
  case TextQuality::SHADED:
    loadedText = TTF_RenderUTF8_Shaded_Wrapped(this->font,
      text.c_str(), this->getForegroundColor(),
      this->getBackgroundColor(), width);
    break;
  case TextQuality::SOLID:
    loadedText = TTF_RenderUTF8_Solid_Wrapped(this->font,
      text.c_str(), this->getForegroundColor(), width);
    break;
  }
  if (!loadedText)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error rendering text", TTF_GetError(),
      theGame.getWindow());
    return false;
  }
  // Convert to texture.
  convertedText = SDL_CreateTextureFromSurface(
    theGame.getRenderer(), loadedText);
  // Free the surfacec
  SDL_FreeSurface(loadedText);
  // If the texture wasn't created, return false.
  if (!convertedText)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error creating a texture", SDL_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error creating a texture: %s.\n", SDL_GetError());
    return false;
  }
  this->textures[name] = convertedText;
  return true;
}

// Render a texture.
bool TextureManager::render(const string &name,
  const SDL_Rect *src, const SDL_Rect *dest, double angle,
  const SDL_Point *center, const SDL_RendererFlip &flip)
{
  // Render the texture.
  if (this->textures.find(name) != this->textures.cend())
  {
    if (SDL_RenderCopyEx(theGame.getRenderer(),
          this->textures[name], src, dest, angle, center,
          flip) < 0)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
        "Error copying a texture in the game's renderer",
        SDL_GetError(), theGame.getWindow());
      SDL_LogError(SDL_LOG_CATEGORY_ERROR,
        "Error copying a texture in the game's renderer: "
        "%s.\n",
        SDL_GetError());
      return false;
    }
  }
  else
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Can't render",
      "The texture to render doesn't exists.",
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Can't render: The texture "
      "to render doesn't exists.\n");
    return false;
  }
  return true;
}

// Render a texture.
bool TextureManager::render(const string &name,
  const SDL_Rect &src, const SDL_Rect &dest)
{
  // Render the texture.
  if (this->textures.find(name) != this->textures.cend())
  {
    if (SDL_RenderCopy(theGame.getRenderer(),
          this->textures[name], &src, &dest) < 0)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
        "Error copying a texture in the game's renderer",
        SDL_GetError(), theGame.getWindow());
      SDL_LogError(SDL_LOG_CATEGORY_ERROR,
        "Error copying a texture in the game's renderer: "
        "%s.\n",
        SDL_GetError());
      return false;
    }
  }
  else
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Can't render",
      "The texture to render doesn't exists.",
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Can't render: The texture "
      "to render doesn't exists.\n");
    return false;
  }
  return true;
}

// Render a texture.
bool TextureManager::render(
  const string &name, const SDL_Rect &dest)
{
  // Render the texture.
  if (this->textures.find(name) != this->textures.cend())
  {
    if (SDL_RenderCopy(theGame.getRenderer(),
          this->textures[name], nullptr, &dest) < 0)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
        "Error copying a texture in the game's renderer",
        SDL_GetError(), theGame.getWindow());
      SDL_LogError(SDL_LOG_CATEGORY_ERROR,
        "Error copying a texture in the game's renderer: "
        "%s.\n",
        SDL_GetError());
      return false;
    }
  }
  else
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Can't render",
      "The texture to render doesn't exists.",
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Can't render: The texture "
      "to render doesn't exist.\n");
    return false;
  }
  return true;
}

// Render a texture.
bool TextureManager::render(
  const string &name, int x, int y)
{
  // Destination area.
  SDL_Rect dest = {x, y, 0, 0};
  if (this->textures.find(name) != this->textures.cend())
  {
    // Get the dimensions of the texture.
    SDL_QueryTexture(this->textures.at(name), nullptr,
      nullptr, &dest.w, &dest.h);
    // Render the texture.
    if (SDL_RenderCopy(theGame.getRenderer(),
          this->textures[name], nullptr, &dest) < 0)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
        "Error copying a texture in the game's renderer",
        SDL_GetError(), theGame.getWindow());
      SDL_LogError(SDL_LOG_CATEGORY_ERROR,
        "Error copying a texture in the game's renderer: "
        "%s.\n",
        SDL_GetError());
      return false;
    }
  }
  else
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Can't render",
      "The texture to render doesn't exists.",
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Can't render: The texture to render doesn't "
      "exists.\n");
    return false;
  }
  return true;
}

// Render a texture with floating precision.
bool TextureManager::render(const string &name,
  const SDL_Rect *src, const SDL_FRect *dest, double angle,
  const SDL_FPoint *center, const SDL_RendererFlip &flip)
{
  // Render the texture.
  if (this->textures.find(name) != this->textures.cend())
  {
    if (SDL_RenderCopyExF(theGame.getRenderer(),
          this->textures[name], src, dest, angle, center,
          flip) < 0)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
        "Error copying a texture in the game's renderer",
        SDL_GetError(), theGame.getWindow());
      SDL_LogError(SDL_LOG_CATEGORY_ERROR,
        "Error copying a texture in the game's renderer: "
        "%s.\n",
        SDL_GetError());
      return false;
    }
  }
  else
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Can't render",
      "The texture to render doesn't exists.",
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Can't render: The texture "
      "to render doesn't exists.\n");
    return false;
  }
  return true;
}

// Render a texture.
bool TextureManager::render(const string &name,
  const SDL_Rect &src, const SDL_FRect &dest)
{
  // Render the texture.
  if (this->textures.find(name) != this->textures.cend())
  {
    if (SDL_RenderCopyF(theGame.getRenderer(),
          this->textures[name], &src, &dest) < 0)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
        "Error copying a texture in the game's renderer",
        SDL_GetError(), theGame.getWindow());
      SDL_LogError(SDL_LOG_CATEGORY_ERROR,
        "Error copying a texture in the game's renderer: "
        "%s.\n",
        SDL_GetError());
      return false;
    }
  }
  else
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Can't render",
      "The texture to render doesn't exists.",
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Can't render: The texture "
      "to render doesn't exists.\n");
    return false;
  }
  return true;
}

// Render a texture.
bool TextureManager::render(
  const string &name, const SDL_FRect &dest)
{
  // Render the texture.
  if (this->textures.find(name) != this->textures.cend())
  {
    if (SDL_RenderCopyF(theGame.getRenderer(),
          this->textures[name], nullptr, &dest) < 0)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
        "Error copying a texture in the game's renderer",
        SDL_GetError(), theGame.getWindow());
      SDL_LogError(SDL_LOG_CATEGORY_ERROR,
        "Error copying a texture in the game's renderer: "
        "%s.\n",
        SDL_GetError());
      return false;
    }
  }
  else
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Can't render",
      "The texture to render doesn't exists.",
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Can't render: The texture "
      "to render doesn't exist.\n");
    return false;
  }
  return true;
}

// Render a text.
bool TextureManager::renderText(const string &text,
  const SDL_Point &dest, double angle,
  const SDL_Point *center, const SDL_RendererFlip &flip)
{
  // The loaded text.
  SDL_Surface *loadedText = nullptr;
  // The converted text.
  SDL_Texture *convertedText = nullptr;
  // Destination area.
  SDL_Rect destRect = {dest.x, dest.y, 0, 0};
  // Load the text.
  switch (this->textRenderingQuality)
  {
  case TextQuality::BLENDED:
    loadedText = TTF_RenderUTF8_Blended(
      this->font, text.c_str(), this->getForegroundColor());
    break;
  case TextQuality::LCD:
    loadedText = TTF_RenderUTF8_LCD(this->font,
      text.c_str(), this->getForegroundColor(),
      this->getBackgroundColor());
    break;
  case TextQuality::SHADED:
    loadedText = TTF_RenderUTF8_Shaded(this->font,
      text.c_str(), this->getForegroundColor(),
      this->getBackgroundColor());
    break;
  case TextQuality::SOLID:
    loadedText = TTF_RenderUTF8_Solid(
      this->font, text.c_str(), this->getForegroundColor());
    break;
  }
  // Verify if the text was loaded.
  if (!loadedText)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error rendering a text", TTF_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error rendering a text: %s.\n", TTF_GetError());
    return false;
  }
  // Convert the surface into texture.
  convertedText = SDL_CreateTextureFromSurface(
    theGame.getRenderer(), loadedText);
  // Free the surface.
  SDL_FreeSurface(loadedText);
  // Verify if the texture was created.
  if (!convertedText)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error creating a texture", SDL_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error creating a texture: %s.\n", SDL_GetError());
    return false;
  }
  // Calculate the area.
  SDL_QueryTexture(convertedText, nullptr, nullptr,
    &destRect.w, &destRect.h);
  // Show the texture.
  if (SDL_RenderCopyEx(theGame.getRenderer(), convertedText,
        nullptr, &destRect, angle, center, flip) < 0)
  {
    SDL_DestroyTexture(convertedText);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error copying a texture", SDL_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error copying a texture: %s.\n", SDL_GetError());
    return false;
  }
  SDL_DestroyTexture(convertedText);
  return true;
}

// Render a text with single floating precision.
bool TextureManager::renderText(const string &text,
  const SDL_FPoint &dest, double angle,
  const SDL_FPoint *center, const SDL_RendererFlip &flip)
{
  // The loaded text.
  SDL_Surface *loadedText = nullptr;
  // The converted text.
  SDL_Texture *convertedText = nullptr;
  // Destination area.
  SDL_FRect destRect = {dest.x, dest.y, 0, 0};
  // Text's texture's width.
  int textureWidth = 0;
  // Text's texture's height.
  int textureHeight = 0;
  // Load the text.
  switch (this->textRenderingQuality)
  {
  case TextQuality::BLENDED:
    loadedText = TTF_RenderUTF8_Blended(
      this->font, text.c_str(), this->getForegroundColor());
    break;
  case TextQuality::LCD:
    loadedText = TTF_RenderUTF8_LCD(this->font,
      text.c_str(), this->getForegroundColor(),
      this->getBackgroundColor());
    break;
  case TextQuality::SHADED:
    loadedText = TTF_RenderUTF8_Shaded(this->font,
      text.c_str(), this->getForegroundColor(),
      this->getBackgroundColor());
    break;
  case TextQuality::SOLID:
    loadedText = TTF_RenderUTF8_Solid(
      this->font, text.c_str(), this->getForegroundColor());
    break;
  }
  // Verify if the text was loaded.
  if (!loadedText)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error rendering a text", TTF_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error rendering a text: %s.\n", TTF_GetError());
    return false;
  }
  // Convert the surface into texture.
  convertedText = SDL_CreateTextureFromSurface(
    theGame.getRenderer(), loadedText);
  // Free the surface.
  SDL_FreeSurface(loadedText);
  // Verify if the texture was created.
  if (!convertedText)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error creating a texture", SDL_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error creating a texture: %s.\n", SDL_GetError());
    return false;
  }
  // Calculate the area.
  SDL_QueryTexture(convertedText, nullptr, nullptr,
    &textureWidth, &textureHeight);
  destRect.w = textureWidth;
  destRect.h = textureHeight;
  // Show the texture.
  if (SDL_RenderCopyExF(theGame.getRenderer(),
        convertedText, nullptr, &destRect, angle, center,
        flip) < 0)
  {
    SDL_DestroyTexture(convertedText);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error copying a texture", SDL_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error copying a texture: %s.\n", SDL_GetError());
    return false;
  }
  SDL_DestroyTexture(convertedText);
  return true;
}

// Render a text.
bool TextureManager::renderText(
  const string &text, int x, int y)
{
  // The loaded text.
  SDL_Surface *loadedText = nullptr;
  // The converted text.
  SDL_Texture *convertedText = nullptr;
  // Destination area.
  SDL_Rect destRect = {x, y, 0, 0};
  // Load the text.
  switch (this->textRenderingQuality)
  {
  case TextQuality::BLENDED:
    loadedText = TTF_RenderUTF8_Blended(
      this->font, text.c_str(), this->getForegroundColor());
    break;
  case TextQuality::LCD:
    loadedText = TTF_RenderUTF8_LCD(this->font,
      text.c_str(), this->getForegroundColor(),
      this->getBackgroundColor());
    break;
  case TextQuality::SHADED:
    loadedText = TTF_RenderUTF8_Shaded(this->font,
      text.c_str(), this->getForegroundColor(),
      this->getBackgroundColor());
    break;
  case TextQuality::SOLID:
    loadedText = TTF_RenderUTF8_Solid(
      this->font, text.c_str(), this->getForegroundColor());
    break;
  }
  // Verify if the text was loaded.
  if (!loadedText)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error rendering a text", TTF_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error rendering a text: %s.\n", TTF_GetError());
    return false;
  }
  // Convert the surface into texture.
  convertedText = SDL_CreateTextureFromSurface(
    theGame.getRenderer(), loadedText);
  // Free the surface.
  SDL_FreeSurface(loadedText);
  // Verify if the texture was created.
  if (!convertedText)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error creating a texture", SDL_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error creating a texture: %s.\n", SDL_GetError());
    return false;
  }
  // Calculate the area.
  SDL_QueryTexture(convertedText, nullptr, nullptr,
    &destRect.w, &destRect.h);
  // Show the texture.
  if (SDL_RenderCopy(theGame.getRenderer(), convertedText,
        nullptr, &destRect) < 0)
  {
    SDL_DestroyTexture(convertedText);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error copying a texture", SDL_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error copying a texture: %s.\n", SDL_GetError());
    return false;
  }
  SDL_DestroyTexture(convertedText);
  return true;
}

// Render a text.
bool TextureManager::renderText(
  const string &text, int x, int y, Uint32 width)
{
  // The loaded text.
  SDL_Surface *loadedText = nullptr;
  // The converted text.
  SDL_Texture *convertedText = nullptr;
  // Destination area.
  SDL_Rect destRect = {x, y, 0, 0};
  // Load the text.
  switch (this->textRenderingQuality)
  {
  case TextQuality::BLENDED:
    loadedText = TTF_RenderUTF8_Blended_Wrapped(this->font,
      text.c_str(), this->getForegroundColor(), width);
    break;
  case TextQuality::LCD:
    loadedText = TTF_RenderUTF8_LCD_Wrapped(this->font,
      text.c_str(), this->getForegroundColor(),
      this->getBackgroundColor(), width);
    break;
  case TextQuality::SHADED:
    loadedText = TTF_RenderUTF8_Shaded_Wrapped(this->font,
      text.c_str(), this->getForegroundColor(),
      this->getBackgroundColor(), width);
    break;
  case TextQuality::SOLID:
    loadedText = TTF_RenderUTF8_Solid_Wrapped(this->font,
      text.c_str(), this->getForegroundColor(), width);
    break;
  }
  // Verify if the text was loaded.
  if (!loadedText)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error rendering a text", TTF_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error rendering a text: %s.\n", TTF_GetError());
    return false;
  }
  // Convert the surface into texture.
  convertedText = SDL_CreateTextureFromSurface(
    theGame.getRenderer(), loadedText);
  // Free the surface.
  SDL_FreeSurface(loadedText);
  // Verify if the texture was created.
  if (!convertedText)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error creating a texture", SDL_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error creating a texture: %s.\n", SDL_GetError());
    return false;
  }
  // Calculate the area.
  SDL_QueryTexture(convertedText, nullptr, nullptr,
    &destRect.w, &destRect.h);
  // Show the texture.
  if (SDL_RenderCopy(theGame.getRenderer(), convertedText,
        nullptr, &destRect) < 0)
  {
    SDL_DestroyTexture(convertedText);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
      "Error copying a texture", SDL_GetError(),
      theGame.getWindow());
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
      "Error copying a texture: %s.\n", SDL_GetError());
    return false;
  }
  // Destroy the texture.
  SDL_DestroyTexture(convertedText);
  return true;
}

// Present the current scene.
void TextureManager::present()
{
  SDL_RenderPresent(theGame.getRenderer());
}

// Change the font used to render text.
bool TextureManager::changeFont(
  const string &path, int size)
{
  return this->openFont(path, size);
}

// Change the size of the font.
bool TextureManager::changeFontSize(int size)
{
  if (this->font)
  {
    if (TTF_SetFontSize(this->font, size) < 0)
      return false;
    return true;
  }
  return false;
}

// Destroy and erase a texture.
void TextureManager::erase(const string &name)
{
  if (this->textures.find(name) != this->textures.cend())
  {
    SDL_DestroyTexture(this->textures[name]);
    this->textures.erase(name);
  }
}

// Destroy and erase all the textures.
void TextureManager::clear()
{
  for (auto &item : this->textures)
  {
    SDL_DestroyTexture(item.second);
    this->textures.erase(item.first);
  }
}

// Set the text rendering quality.
void TextureManager::setTextQuality(
  const TextQuality &quality)
{
  this->textRenderingQuality = quality;
}

// Get the text rendering quality.
const TextQuality &TextureManager::getTextQuality()
{
  return this->textRenderingQuality;
}

// Set the foreground rendering color.
void TextureManager::setForegroundColor(
  const SDL_Color &color)
{
  this->foregroundTextColor = color;
}

// Get the text rendering color.
const SDL_Color &TextureManager::getForegroundColor()
{
  return this->foregroundTextColor;
}

// Set the foreground text rendering color.
void TextureManager::setBackgroundColor(
  const SDL_Color &color)
{
  this->backgroundTextColor = color;
}

// Get the background rendering text color.
const SDL_Color &TextureManager::getBackgroundColor()
{
  return this->backgroundTextColor;
}

// Get a texture.
const SDL_Texture *TextureManager::getTexture(
  const string &name)
{
  if (this->textures.find(name) != this->textures.cend())
    return this->textures[name];
  return nullptr;
}

// Get a modifiable texture.
SDL_Texture *TextureManager::getModifiableTexture(
  const string &name)
{
  if (this->textures.find(name) != this->textures.cend())
    return this->textures[name];
  return nullptr;
}

// Get the instance of the class.
TextureManager &TextureManager::getInstance()
{
  static TextureManager theInstance;
  return theInstance;
}
