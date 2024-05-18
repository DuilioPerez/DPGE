// File: Button.cpp
// Author: Duilio Pérez
// Implementation of the label widget.
#include "Button.hpp"
#include "Game.hpp"
using namespace DPGE;
using namespace std;

// Constructor.
Button::Button(const SDL_Rect &buttonArea)
{
  this->area = buttonArea;
}

// Set the area of the button.
void Button::setArea(const SDL_Rect &buttonArea)
{
  this->area = buttonArea;
}

// Set the event manager.
void Button::setEventManager(
  BasicEventListenerManager &nextEventManager)
{
  this->eventManager = nextEventManager;
}

// Get the event manager.
BasicEventListenerManager &Button::getEventManager()
{
  return this->eventManager;
}

// Set the layers of the widget.
void Button::setLayers(
  const list<TextureInfo> &widgetLayers)
{
  this->layers = widgetLayers;
}

// Get the area of the button.
const SDL_Rect &Button::getArea() const
{
  return this->area;
}

// Get the layers of the current widget.
const list<TextureInfo> &Button::getLayers() const
{
  return this->layers;
}

// Render the widget.
void Button::render()
{
  // Window's dimensions.
  int windowWidth, windowHeight;
  // Default area for rendering.
  SDL_Rect defaultSrc, defaultDest;
  // Clipped source area to render.
  SDL_Rect *clippedSrc = nullptr;
  // Clipped destination area where texture will be
  // rendered.
  SDL_Rect *clippedDest = nullptr;
  // Texture to query dimensions.
  SDL_Texture *texture = nullptr;
  // Difference between dimension one and dimension two.
  Uint32 diff = 0;
  // Get the window's size.
  SDL_GetWindowSize(
    theGame.getWindow(), &windowWidth, &windowHeight);
  // Loop to render.
  for (const TextureInfo &nextLayer : this->layers)
  {
    // Texture dimensions.
    clippedSrc  = nextLayer.src;
    clippedDest = nextLayer.dest;
    // If clippedSrc is nullptr, use the complete texture's
    // size.
    if (!clippedSrc)
    {
      texture = theTextureManager.getModifiableTexture(
        nextLayer.name);
      SDL_QueryTexture(
        texture, NULL, NULL, &defaultSrc.w, &defaultSrc.h);
      defaultSrc.x = 0;
      defaultSrc.y = 0;
      clippedSrc   = &defaultSrc;
    }
    // If clippedDest is nullptr, use window's complete
    // dimensions.
    if (!clippedDest)
    {
      defaultDest.x = 0;
      defaultDest.y = 0;
      defaultDest.w = windowWidth;
      defaultDest.h = windowHeight;
      clippedDest   = &defaultDest;
    }
    // Clip destination area to fit button's area.
    if (clippedDest->x < area.x)
    {
      diff = this->area.x - clippedDest->x;
      clippedSrc->x += diff;
      clippedSrc->w -= diff;
      clippedDest->x = area.x;
      clippedDest->w -= diff;
    }
    if (clippedDest->y < this->area.y)
    {
      diff = this->area.y - clippedDest->y;
      clippedSrc->y += diff;
      clippedSrc->h -= diff;
      clippedDest->y = this->area.y;
      clippedDest->h -= diff;
    }
    if (clippedDest->x + clippedDest->w >
        this->area.x + this->area.w)
    {
      diff = (clippedDest->x + clippedDest->w) -
             (this->area.x + this->area.w);
      clippedSrc->w -= diff;
      clippedDest->w -= diff;
    }
    if (clippedDest->y + clippedDest->h >
        this->area.y + this->area.h)
    {
      diff = (clippedDest->y + clippedDest->h) -
             (this->area.y + this->area.h);
      clippedSrc->h -= diff;
      clippedDest->h -= diff;
    }
    // Be sure dimensions aren't negative.
    if (clippedSrc->w > 0 && clippedSrc->h > 0 &&
        clippedDest->w > 0 && clippedDest->h > 0)
    {
      theTextureManager.render(
        nextLayer.name, clippedSrc, clippedDest);
    }
  }
}

// Update the widget.
void Button::update(void (*function)(list<TextureInfo> &))
{
  function(this->layers);
}

// Handle the events
void Button::handleEvents(const SDL_Event &topEvent)
{
  this->eventManager.handleEvents(topEvent);
}
