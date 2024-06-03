/// @file EventHandler.hpp
/// @author Duilio Pérez
/// @brief A class to wotk with common events.
#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP true
#include <SDL2/SDL.h>
#include <map>
#include <string>

namespace DPGE
{

  /// @brief The game events.
  enum struct EventType
  {
    /// @brief An event with the audio device.
    AUDIODEVICE,
    /// @brief Game controller axis motion.
    CONTROLLERAXIS,
    /// @brief Game controller button event.
    CONTROLLERBUTTON,
    /// @brief Game controller device event.
    CONTROLLERDEVICE,
    /// @brief Dollar gesture event.
    DOLLARGESTURE,
    /// @brief Drop event.
    DROP,
    /// @brief Touch finger event.
    FINGER,
    /// @brief Keyboard event.
    KEYBOARD,
    /// @brief Joystick axis motion events.
    JOYAXIS,
    /// @brief Joystick ball motion event.
    JOYBALL,
    /// @brief Joystick hat motion event.
    JOYHAT,
    /// @brief Joystick button event.
    JOYBUTTON,
    /// @brief Joystick device event.
    JOYDEVICE,
    /// @brief Mouse motion event.
    MOUSEMOTION,
    /// @brief Mouse button event.
    MOUSEBUTTON,
    /// @brief Mouse wheel event.
    MOUSEWHEEL,
    /// @brief Multigesture event.
    MULTIGESTURE,
    /// @brief Quit event.
    QUIT,
    /// @brief Specific video driver event.
    SYSWM,
    /// @brief Text editing event.
    TEXTEDITING,
    /// @brief Text input event.
    TEXTINPUT,
    /// @brief A user defined event.
    USER,
    /// @brief Window event.
    WINDOW
  };

  /// @brief A class to handle events of a game object.
  template <typename T>
  class EventListener final
  {
  public:
    /// @brief Default constructor.
    EventListener() = default;
    /// @brief Create an event handler using a data struct.
    /// @param dataStruct The data to use.
    EventListener(T *dataStruct) : data{dataStruct} {};
    /// @brief Add an event listener.
    /// @param event The event to listen.
    /// @param function The function to register.
    void addEventListener(const EventType &event,
      void (*function)(T *data, const SDL_Event &))
    {
      // If the function isn't nullptr, add the event
      // listener.
      if (function)
        this->eventListeners[event] = function;
      // Otherwise delete the current event listener.
      else
        this->eventListeners.erase(event);
    }
    /// @brief Remove the event listener.
    /// @param event The event to remove its listener.
    void removeEventListener(const EventType &event)
    {
      // If there is an event listener, remove it.
      if (this->eventListeners.find(event) !=
          this->eventListeners.cend())
        this->eventListeners.erase(event);
    }
    /// @brief Handle the events.
    /// @param event The even to handle.
    void handleEvents(const SDL_Event &event)
    {
      switch (event.type)
      {
      case SDL_AUDIODEVICEADDED:
      case SDL_AUDIODEVICEREMOVED:
        this->callFunction(EventType::AUDIODEVICE, event);
        break;
      case SDL_CONTROLLERAXISMOTION:
        this->callFunction(
          EventType::CONTROLLERAXIS, event);
        break;
      case SDL_CONTROLLERBUTTONDOWN:
      case SDL_CONTROLLERBUTTONUP:
        this->callFunction(
          EventType::CONTROLLERBUTTON, event);
        break;
      case SDL_CONTROLLERDEVICEADDED:
      case SDL_CONTROLLERDEVICEREMAPPED:
      case SDL_CONTROLLERDEVICEREMOVED:
        this->callFunction(
          EventType::CONTROLLERDEVICE, event);
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
    /// @brief Set the data structure.
    /// @param dataStruct The data struct to use.
    void setData(T *dataStruct)
    {
      this->data = dataStruct;
    }

  private:
    /// @brief Call a function defined to handle the event.
    /// @param event The event type to handle.
    void callFunction(
      const EventType &event, const SDL_Event &topEvent)
    {
      // Call the function if is defined.
      if (this->eventListeners.find(event) !=
          this->eventListeners.cend())
        this->eventListeners[event](this->data, topEvent);
    }
    /// @brief Data for the event handler.
    T *data;
    /// @brief All the event listeners.
    std::map<EventType, void (*)(T *, const SDL_Event &)>
      eventListeners;
  };

  /// @brief A class to handle events of a game object
  /// without a data structure.
  class BasicEventListener final
  {
  public:
    /// @brief Add an event listener.
    /// @param event The event to listen.
    /// @param function The function to register.
    void addEventListener(const EventType &event,
      void (*function)(const SDL_Event &));
    /// @brief Remove the event listener.
    /// @param event The event to remove its listener.
    void removeEventListener(const EventType &event);
    /// @brief Handle the events.
    /// @param event The even to handle.
    void handleEvents(const SDL_Event &event);

  private:
    /// @brief Call a function defined to handle the event.
    /// @param event The event type to handle.
    void callFunction(
      const EventType &event, const SDL_Event &topEvent);
    /// @brief All the event listeners.
    std::map<EventType, void (*)(const SDL_Event &)>
      eventListeners;
  };

  /// @brief An event handler.
  class EventHandler final
  {
  public:
    /// @brief Deleted copy constructor.
    EventHandler(const EventHandler &) = delete;
    /// @brief Add an event listener id to its map.
    /// @param id The id of the event listener manager.
    /// @param data The data struct to manipulate.
    void addEventListenerManager(
      const std::string &id, void *data);
    /// @brief Add a basic event listener.
    /// @param id The id of the event listener manager.
    void addBasicEventListener(const std::string &id);
    /// @brief Handle the events.
    /// @param topEvent The event in the top of the stack.
    void handleEvents(const SDL_Event &topEvent);
    /// @brief Get a pointer to an event listener manager.
    /// @param id The id of the event listener.
    /// @return The event listener manager, or nullptr in
    /// error.
    EventListener<void *> *getEventListener(
      const std::string &id);
    /// @brief Get a pointer to a basic event listener
    /// manager.
    /// @param id The id of the event listener.
    /// @return The event listener manager, or nullptr in
    /// error.
    BasicEventListener *getBasicEventListener(
      const std::string &id);
    /// @brief Erase an event listener manager.
    /// @param id The id of the event listener manager.
    void eraseEventListener(const std::string &id);
    /// @brief Erase a basic event listener manager.
    /// @param id The event listener manager's id.
    void eraseBasicEventListener(const std::string &id);
    /// @brief Remove all the normal event listener
    /// managers.
    void clearEventListeners();
    /// @brief Remove all the basic event listener managers.
    void clearBasicEventListeners();
    /// @brief Clear all the event listener manager, both
    /// normal and basic.
    void clear();
    /// @brief Get the class' instance.
    static EventHandler &getInstance();
    /// @brief Deleted copy operator.
    const EventHandler &operator=(
      const EventHandler) = delete;

  private:
    /// @brief Default constructor.
    EventHandler() = default;
    /// @brief Normal event listeners.
    std::map<std::string, EventListener<void *>>
      eventListeners;
    /// @brief Basic event listeners.
    std::map<std::string, BasicEventListener>
      basicEventListeners;
  };

  /// @brief A reference to the EventHandler object.
  extern EventHandler &theEventHandler;

} // namespace DPGE

#endif
