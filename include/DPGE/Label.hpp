/// @file Label.hpp
/// @author Duilio Pérez
/// @brief The label widget.
#ifndef LABEL_HPP
#define LABEL_HPP
#include "Widget.hpp"
#include <SDL2/SDL.h>

namespace DPGE
{

  /// @brief The labe widget.
  class Label final : public Widget
  {
  public:
    // Overriden functions.
    void handleEvents() override;
    void update() override;
    void render() override;

  private:
    /// @brief The area of the label.
    SDL_Rect area;
    /// @brief The label's string.
    const char *text = nullptr;
  };

} // namespace DPGE

#endif
