// File: EventHandle.cpp
// Author: Duilio Pérez
// Event handler's implementation.
#include "EventHandler.hpp"
#include <string>
using namespace DPGE;
using namespace std;

// The EventHandler object.
EventHandler &DPGE::theEventHandler =
  EventHandler::getInstance();

// Add an event handler.
void BasicEventListener::addEventListener(
  const EventType &event,
  void (*function)(const SDL_Event &))
{
  // If the function isn't nullptr, add the event
  // listener.
  if (function)
    this->eventListeners[event] = function;
  // Otherwise delete the current event listener.
  else
    this->eventListeners.erase(event);
}

// Remove an event listener.
void BasicEventListener::removeEventListener(
  const EventType &event)
{
  // If there is an event listener, remove it.
  if (this->eventListeners.find(event) !=
      this->eventListeners.cend())
    this->eventListeners.erase(event);
}

// Handle the events.
void BasicEventListener::handleEvents(
  const SDL_Event &event)
{
  switch (event.type)
  {
  case SDL_AUDIODEVICEADDED:
  case SDL_AUDIODEVICEREMOVED:
    this->callFunction(EventType::AUDIODEVICE, event);
    break;
  case SDL_CONTROLLERAXISMOTION:
    this->callFunction(EventType::CONTROLLERAXIS, event);
    break;
  case SDL_CONTROLLERBUTTONDOWN:
  case SDL_CONTROLLERBUTTONUP:
    this->callFunction(EventType::CONTROLLERBUTTON, event);
    break;
  case SDL_CONTROLLERDEVICEADDED:
  case SDL_CONTROLLERDEVICEREMAPPED:
  case SDL_CONTROLLERDEVICEREMOVED:
    this->callFunction(EventType::CONTROLLERDEVICE, event);
    break;
  case SDL_DOLLARGESTURE:
  case SDL_DOLLARRECORD:
    this->callFunction(EventType::DOLLARGESTURE, event);
    break;
  case SDL_DROPBEGIN:
  case SDL_DROPCOMPLETE:
  case SDL_DROPFILE:
  case SDL_DROPTEXT:
    this->callFunction(EventType::DROP, event);
    break;
  case SDL_FINGERDOWN:
  case SDL_FINGERUP:
  case SDL_FINGERMOTION:
    this->callFunction(EventType::FINGER, event);
    break;
  case SDL_KEYDOWN:
  case SDL_KEYUP:
    this->callFunction(EventType::KEYBOARD, event);
    break;
  case SDL_JOYAXISMOTION:
    this->callFunction(EventType::JOYAXIS, event);
    break;
  case SDL_JOYBALLMOTION:
    this->callFunction(EventType::JOYBALL, event);
    break;
  case SDL_JOYBUTTONDOWN:
  case SDL_JOYBUTTONUP:
    this->callFunction(EventType::JOYBUTTON, event);
    break;
  case SDL_JOYDEVICEADDED:
  case SDL_JOYDEVICEREMOVED:
    this->callFunction(EventType::JOYDEVICE, event);
    break;
  case SDL_JOYHATMOTION:
    this->callFunction(EventType::JOYHAT, event);
    break;
  case SDL_MOUSEMOTION:
    this->callFunction(EventType::MOUSEMOTION, event);
    break;
  case SDL_MOUSEBUTTONDOWN:
  case SDL_MOUSEBUTTONUP:
    this->callFunction(EventType::MOUSEBUTTON, event);
    break;
  case SDL_MOUSEWHEEL:
    this->callFunction(EventType::MOUSEWHEEL, event);
    break;
  case SDL_MULTIGESTURE:
    this->callFunction(EventType::MULTIGESTURE, event);
    break;
  case SDL_QUIT:
    this->callFunction(EventType::QUIT, event);
    break;
  case SDL_SYSWMEVENT:
    this->callFunction(EventType::SYSWM, event);
    break;
  case SDL_TEXTEDITING:
    this->callFunction(EventType::TEXTEDITING, event);
    break;
  case SDL_TEXTINPUT:
    this->callFunction(EventType::TEXTINPUT, event);
    break;
  case SDL_USEREVENT:
    this->callFunction(EventType::USER, event);
    break;
  case SDL_WINDOWEVENT:
    this->callFunction(EventType::WINDOW, event);
    break;
  default:
    break;
  }
}

// Call a function based on the event.
void BasicEventListener::callFunction(
  const EventType &event, const SDL_Event &topEvent)
{
  // Call the function if is defined.
  if (this->eventListeners.find(event) !=
      this->eventListeners.cend())
    this->eventListeners[event](topEvent);
}

// Add an event listener manager to the event handler.
void EventHandler::addEventListenerManager(
  const string &id, void *data)
{
  // Insert it if there is not one with that id.
  if (this->eventListeners.find(id) !=
      this->eventListeners.cend())
    this->eventListeners[id].setData(&data);
}

// Add a basic event listener manager to the event handler.
void EventHandler::addBasicEventListener(const string &id)
{
  // Insert it if there is not one with that id.
  if (this->eventListeners.find(id) !=
      this->eventListeners.cend())
    this->basicEventListeners[id] = BasicEventListener();
}

// Make the event listener managers to handle the events.
void EventHandler::handleEvents(const SDL_Event &topEvent)
{
  // Normal event listener managers.
  for (auto &item : this->eventListeners)
    item.second.handleEvents(topEvent);
  // Basic event listener managers.
  for (auto &item : this->basicEventListeners)
    item.second.handleEvents(topEvent);
}

// Get an event listener manager.
EventListener<void *> *EventHandler::getEventListener(
  const string &id)
{
  // Return the event handler if is found.
  if (this->eventListeners.find(id) !=
      this->eventListeners.cend())
    return &this->eventListeners[id];
  return nullptr;
}

// Get a basic event listener manager.
BasicEventListener *EventHandler::getBasicEventListener(
  const string &id)
{
  // Return the event handler if is found.
  if (this->basicEventListeners.find(id) !=
      this->basicEventListeners.cend())
    return &this->basicEventListeners[id];
  return nullptr;
}

// Erase an event listener manager.
void EventHandler::eraseEventListener(const string &id)
{
  // Erase it if is found.
  if (this->eventListeners.find(id) !=
      this->eventListeners.cend())
    this->eventListeners.erase(id);
}

// Erase a basic event listener manager.
void EventHandler::eraseBasicEventListener(const string &id)
{
  // Erase it if is found.
  if (this->basicEventListeners.find(id) !=
      this->basicEventListeners.cend())
    this->basicEventListeners.erase(id);
}

// Delete all the normal event listener manager.
void EventHandler::clearEventListeners()
{
  this->eventListeners.clear();
}

// Delete all the basic event listener manager.
void EventHandler::clearBasicEventListeners()
{
  this->basicEventListeners.clear();
}

// Delete all the event listener manager, normal and basic.
void EventHandler::clear()
{
  this->eventListeners.clear();
  this->basicEventListeners.clear();
}

// Get the class' instance.
EventHandler &EventHandler::getInstance()
{
  static EventHandler theEventHandler;
  return theEventHandler;
}
