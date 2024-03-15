/// @file GameObject.hpp
/// @author Duilio Pérez
/// @brief A generic game object.
#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP true

namespace DPGE
{

  /// @brief A generic game object.
  class GameObject
  {
  public:
    /// @brief Handle the game object's events.
    virtual void handleEvents() = 0;
    /// @brief Update the game object.
    virtual void update() = 0;
    /// @brief Render the game object.
    virtual void render() = 0;
    /// @brief Virtual destructor.
    virtual ~GameObject(){};
  };

} // namespace DPGE

#endif
