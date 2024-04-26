// File: Button.cpp
// Author: Duilio Pérez
// Implementation of the label widget.
#include "Button.hpp"
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
  for (const TextureInfo &nextLayer : this->layers)
  {
    theTextureManager.render(
      nextLayer.name, nextLayer.src, nextLayer.dest);
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
