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
void Button::setEventListener(
  BasicEventListener &nextEventManager)
{
  this->eventManager = nextEventManager;
}

// Get the event manager.
BasicEventListener &Button::getEventListener()
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

void Button::render()
{
  // Texture's size.
  SDL_Rect textureSize = {0, 0, 0, 0};
  // Game's window's size.
  SDL_Rect windowSize = {0, 0, 0, 0};
  // Clipped source area.
  SDL_Rect clippedSrc = {0, 0, 0, 0};
  // Clipped destination area.
  SDL_Rect clippedDest = {0, 0, 0, 0};
  // Horizontal and vertical scaling factors.
  float xScale = 0;
  float yScale = 0;
  // Value to increase or decrease
  int delta = 0;
  // Render every texture of the button.
  for (TextureInfo nextLayer : this->layers)
  {
    // If the source is nullptr, query the texture's size.
    if (!nextLayer.src)
    {
      if (SDL_QueryTexture(
            theTextureManager.getModifiableTexture(
              nextLayer.name),
            nullptr, nullptr, &textureSize.w,
            &textureSize.h) < 0)
      {
        SDL_Log(
          "Failed to query texture: %s\n", SDL_GetError());
        continue; // Skip this layer if texture query fails.
      }
      nextLayer.src = &textureSize;
    }
    // Same for destination rectangle.
    if (!nextLayer.dest)
    {
      SDL_GetWindowSize(
        theGame.getWindow(), &windowSize.w, &windowSize.h);
      nextLayer.dest = &windowSize;
    }
    // Don't render if width or height is non-positive.
    if (nextLayer.src->w <= 0 || nextLayer.src->h <= 0 ||
        nextLayer.dest->w <= 0 || nextLayer.dest->h <= 0)
      continue;
    // Clipping and scaling algorithm.
    if (nextLayer.dest->x >= this->area.x &&
        nextLayer.dest->y >= this->area.y &&
        nextLayer.dest->x + nextLayer.dest->w <=
          this->area.x + this->area.w &&
        nextLayer.dest->y + nextLayer.dest->h <=
          this->area.y + this->area.h)
      // Destination is completely within the button area
      theTextureManager.render(
        nextLayer.name, nextLayer.src, nextLayer.dest);
    else if (nextLayer.dest->x + nextLayer.dest->w <
               this->area.x ||
             nextLayer.dest->y + nextLayer.dest->h <
               this->area.y ||
             nextLayer.dest->x >
               this->area.x + this->area.w ||
             nextLayer.dest->y >
               this->area.y + this->area.h)
      // Destination is completely outside the button area
      continue;
    else
    {
      // Calculate horizontal and vertical scaling factors.
      xScale = static_cast<float>(nextLayer.src->w) /
               nextLayer.dest->w;
      yScale = static_cast<float>(nextLayer.src->h) /
               nextLayer.dest->h;
      // Set clipped source area to full source initially.
      clippedSrc = *nextLayer.src;
      // Set clipped destination area to full destination
      // initially.
      clippedDest = *nextLayer.dest;
      // Adjust source and destination rectangles based on
      // button boundaries.
      if (nextLayer.dest->x < this->area.x)
      {
        delta = (this->area.x - nextLayer.dest->x) * xScale;
        clippedSrc.x += delta;
        clippedDest.x = this->area.x;
      }
      if (nextLayer.dest->y < this->area.y)
      {
        delta = (this->area.y - nextLayer.dest->y) * yScale;
        clippedSrc.y += delta;
        clippedDest.y = this->area.y;
      }
      if (clippedDest.x + clippedDest.w >
          this->area.x + this->area.w)
      {
        delta = ((clippedDest.x + clippedDest.w) -
                  (this->area.x + this->area.w)) *
                xScale;
        clippedSrc.w -= delta;
        clippedDest.w =
          this->area.x + this->area.w - clippedDest.x;
      }
      if (clippedDest.y + clippedDest.h >
          this->area.y + this->area.h)
      {
        delta = ((clippedDest.y + clippedDest.h) -
                  (this->area.y + this->area.h)) *
                yScale;
        clippedSrc.h -= delta;
        clippedDest.h =
          this->area.y + this->area.h - clippedDest.y;
      }
      // Render the clipped area if valid.
      if (clippedSrc.w > 0 && clippedSrc.h > 0 &&
          clippedDest.w > 0 && clippedDest.h > 0)
        theTextureManager.render(
          nextLayer.name, clippedSrc, clippedDest);
    }
  }
}

// Update the widget.
void Button::update(void (*function)(list<TextureInfo> &))
{
  if (function)
    function(this->layers);
}

// Handle the events
void Button::handleEvents(const SDL_Event &topEvent)
{
  this->eventManager.handleEvents(topEvent);
}
