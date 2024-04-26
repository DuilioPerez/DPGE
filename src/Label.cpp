// File: Label.cpp
// Author: Duilio Pérez
// Implementation of the label widget.
#include "Label.hpp"
using namespace DPGE;
using namespace std;

// Constructor.
Label::Label(const SDL_Rect &labelArea)
{
  this->area = labelArea;
}

// Set the area of the label.
void Label::setArea(const SDL_Rect &labelArea)
{
  this->area = labelArea;
}

// Set the layers of the widget.
void Label::setLayers(const list<TextureInfo> &widgetLayers)
{
  this->layers = widgetLayers;
}

// Get the area of the label.
const SDL_Rect &Label::getArea() const
{
  return this->area;
}

// Get the layers of the current widget.
const list<TextureInfo> &Label::getLayers() const
{
  return this->layers;
}

// Render the widget.
void Label::render()
{
  for (const TextureInfo &nextLayer : this->layers)
    theTextureManager.render(
      nextLayer.name, nextLayer.src, nextLayer.dest);
}

// Update the widget.
void Label::update(void (*function)(list<TextureInfo> &))
{
  function(this->layers);
}
