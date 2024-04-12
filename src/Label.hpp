/// @file Label.hpp
/// @author Duilio Pérez
/// @brief The label widget.
#ifndef LABEL_HPP
#define LABEL_HPP
#include "TextureManager.hpp"
#include "Widget.hpp"
#include <SDL2/SDL.h>
#include <list>

namespace DPGE
{

  /// @brief The labe widget.
  class Label final : public Widget
  {
  public:
    /// @brief Get the layers of the label.
    /// @return The layers of the label.
    const std::list<TextureInfo> &getLayers() const;
    /// @brief Set the layers of the label.
    /// @param layers The layers of the label.
    void setLayers(const std::list<TextureInfo> &layers);
    /// @brief Update the current widget
    /// @param function The function to call to update.
    void update(void (*function)(std::list<TextureInfo> &));
    /// @brief Overriden funtion to render the widget.
    void render() override;

  private:
    /// @brief The information of the textures of the label.
    std::list<TextureInfo> layers;
  };

} // namespace DPGE

#endif
