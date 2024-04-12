/// @file Widget.hpp
/// @author Duilio Pérez
/// @brief A generic Widget.
#ifndef WIDGET_HPP
#define WIDGET_HPP true
#include <SDL2/SDL.h>

namespace DPGE
{

  /// @brief A class that represents a generic widget.
  class Widget
  {
  public:
    /// @brief Render a widget.
    virtual void render() = 0;
    /// @brief Virtual destructor.
    virtual ~Widget(){};
  };

} // namespace DPGE

#endif
