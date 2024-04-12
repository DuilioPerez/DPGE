/// @file Button.hpp
/// @author Duilio Pérez
/// @brief The label widget.
#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "EventHandler.hpp"
#include "TextureManager.hpp"
#include "Widget.hpp"
#include <SDL2/SDL.h>
#include <list>

namespace DPGE
{

  /// @brief The labe widget.
  class Button final : public Widget
  {
  public:
    /// @brief Get the layers of the label.
    /// @return The layers of the label.
    const std::list<TextureInfo> &getLayers() const;
    /// @brief Set the event manager of the button.
    /// @param eventManager The event manager to set.
    void setEventManager(
      BasicEventListenerManager &eventManager);
    /// @brief Set the layers of the label.
    /// @param layers The layers of the label.
    void setLayers(const std::list<TextureInfo> &layers);
    /// @brief Update the current widget
    /// @param function The function to call to update.
    void update(void (*function)(std::list<TextureInfo> &));
    /// @brief Handle the events.
    /// @param topEvent The next event to proccess.
    void handleEvents(const SDL_Event &topEvent);
    /// @brief Overriden funtion to render the widget.
    void render() override;

  private:
    /// @brief The information of the textures of the label.
    std::list<TextureInfo> layers;
    /// @brief The event handler.
    BasicEventListenerManager eventManager;
  };

} // namespace DPGE

#endif