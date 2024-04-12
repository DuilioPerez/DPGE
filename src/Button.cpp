// File: Button.cpp
// Author: Duilio Pérez
// Implementation of the label widget.
#include "Button.hpp"
using namespace DPGE;
using namespace std;

// Set the event manager.
void Button::setEventManager(
  BasicEventListenerManager &nextEventManager)
{
  this->eventManager = nextEventManager;
}

// Set the layers of the widget.
void Button::setLayers(
  const list<TextureInfo> &widgetLayers)
{
  this->layers = widgetLayers;
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
    theTextureManager.render(
      nextLayer.name, nextLayer.src, nextLayer.dest);
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
