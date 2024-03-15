/// @file Widget.hpp
/// @author Duilio Pérez
/// @brief A generic Widget.
#ifndef WIDGET_HPP
#define WIDGET_HPP true

namespace DPGE
{

  /// @brief A class that represents a generic widget.
  class Widget
  {
  public:
    /// @brief Handle the widget's events.
    virtual void handleEvents() = 0;
    /// @brief Update the widget.
    virtual void update() = 0;
    /// @brief Render the widget.
    virtual void render() = 0;
    /// @brief Virtual destructor.
    virtual ~Widget(){};
  };

} // namespace DPGE

#endif
