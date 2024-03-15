/// @file Vector2.hpp
/// @author Duilio Pérez.
/// @brief Define classes to work with vectors 2D.
///
/// A vector 2D is an magnitude with direction. It can be
/// used in many different ways, for example, to represent
/// motion and speed.

#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP true
#include <SDL2/SDL.h>
#include <cmath>

namespace DPGE
{
  /// @brief Class to work with vectors 2D.
  ///
  /// This class allows to work with vectors 2D in an easy
  /// way.
  template <typename Type>
  class Vector2D final
  {
  public:
    // Constructors and Destructors.
    /// @brief Default constructor.
    Vector2D() noexcept : x{0}, y{0}
    {
    }
    /// @brief Default copy constructor.
    Vector2D(const Vector2D &) = default;
    /// @brief Create a vector with a defined position.
    /// @param xPos X cartesian coordinate.
    /// @param yPos Y cartesian coordinate.
    Vector2D(const Type &xPos, const Type &yPos)
    : x{xPos}, y{yPos}
    {
    }
    // Setters and Getters.
    /// @brief Set the position of the vector.
    /// @param xPos X coordinate of the vector.
    /// @param yPos Y coordinate of the vector.
    void setPosition(
      const Type &xPos, const Type &yPos) noexcept
    {
      this->setX(xPos);
      this->setY(yPos);
    }
    /// @brief Get the position of the vector.
    /// @param xPos X cartesian coordinate.
    /// @param yPos Y cartesian coordinate.
    void getPosition(Type &xPos, Type &yPos) const noexcept
    {
      xPos = this->getX();
      yPos = this->getY();
    }
    /// @brief Set the x position of the vector.
    /// @param xpos X coordinate of the vector.
    void setX(const Type &xPos) noexcept
    {
      this->x = xPos;
    }
    /// @brief Get the x position of the vector.
    /// @return The x position of the vector.
    const Type &getX() const noexcept
    {
      return this->x;
    }
    /// @brief Set the y position of the vector.
    /// @param ypos Y coordinate of the vector.
    void setY(const Type &yPos) noexcept
    {
      this->x = yPos;
    }
    /// @brief Get the y position of the vector.
    /// @return The y position of the vector.
    const Type &getY() const noexcept
    {
      return this->y;
    }
    /// @brief Get the length of the vector.
    /// @return The length of the vector.
    const Type &getLength() const noexcept
    {
      // Pythagoras theorem (a^2 = b^2 + c^2).
      return sqrt(
        pow(this->getX(), 2) + pow(this->getY(), 2));
    }
    // Utilitaty functions.
    /// @brief Normalize a vector.
    void normalize() noexcept
    {
      // Normalization (v_n = v * 1 / l).
      if (this->getLength() != 0)
        *this *= 1 / this->getLength();
    }
    // Overloaded operators.
    /// @brief Adds two vectors.
    /// @param addVector Vector to add.
    /// @return The result of the addition.
    const Vector2D<Type> operator+(
      const Vector2D &addVector) const noexcept
    {
      return Vector2D<Type>(this->getX() + addVector.getX(),
        this->getY() + addVector.getY());
    }
    /// @brief Adds a vector with another and hold the
    /// result.
    /// @param addVector Vector to add.
    /// @return The result of the addition.
    const Vector2D<Type> &operator+=(
      const Vector2D<Type> &addVector) noexcept
    {
      this->setX(this->getX() + addVector.getX());
      this->setY(this->getY() + addVector.getY());
      return *this;
    }
    /// @brief Subtract two vectors.
    /// @param subVector Vector to subtract.
    /// @return The result of the subtraction.
    const Vector2D<Type> operator-(
      const Vector2D &subVector) const noexcept
    {
      return Vector2D<Type>(this->getX() - subVector.getX(),
        this->getY() - subVector.getY());
    }
    /// @brief Subtract a vector with another and hold the
    /// result.
    /// @param subVector Vector to subtract.
    /// @return The result of the subtraction.
    const Vector2D<Type> &operator-=(
      const Vector2D<Type> &subVector) noexcept
    {
      this->setX(this->getX() - subVector.getX());
      this->setY(this->getY() - subVector.getY());
      return *this;
    }
    /// @brief Multiplication operator.
    /// @param scalar Magnitude to multiply.
    /// @return The result of the operation.
    const Vector2D operator*(
      const Type &scalar) const noexcept
    {
      return Vector2D<Type>(
        this->getX() * scalar, this->getY() * scalar);
    }
    /// @brief Multiply a vector by a scalar and hold the
    /// result.
    /// @param scalar Magnitude to multiply.
    /// @return The result of the operation.
    const Vector2D &operator*=(const Type &scalar) noexcept
    {
      this->setX(this->getX() * scalar);
      this->setY(this->getY() * scalar);
      return *this;
    }
    /// @brief Divide a vector by a scalar.
    /// @param scalar Magnitude to use as denominator.
    /// @return The result of the operation.
    ///
    /// If the scalar is 0, return a vector to 0,0.
    const Vector2D operator/(
      const Type &scalar) const noexcept
    {
      if (scalar != 0)
        return Vector2D<Type>(
          this->getX() / scalar, this->getY() / scalar);
      return Vector2D<Type>(0, 0);
    }
    /// @brief Divide a vector by a scalar and hold the
    /// result.
    /// @param scalar Magnitude to be used as denominator.
    /// @return The result of the operation.
    ///
    /// If the scalar is 0, return a vector to 0,0.
    const Vector2D &operator/=(const Type &scalar) noexcept
    {
      if (scalar != 0)
      {
        this->setX(this->getX() / scalar);
        this->setY(this->getY() / scalar);
        return *this;
      }
      return Vector2D<Type>(0, 0);
    }

  private:
    /// @brief X coordinate of the vector.
    Type x;
    /// @brief Y coordinate of the vector.
    Type y;
  };

  // Synonyms of types.

  /// @brief Vector 2D of type char.
  typedef Vector2D<char> Vector2c;
  /// @brief Vector 2D of type unsigned char.
  typedef Vector2D<unsigned char> Vector2uc;
  /// @brief Vector 2D of type short.
  typedef Vector2D<short> Vector2s;
  /// @brief Vector 2D of type unsigned short.
  typedef Vector2D<unsigned short> Vector2us;
  /// @brief Vector 2D of type int.
  typedef Vector2D<int> Vector2i;
  /// @brief Vector 2D of type unsigned.
  typedef Vector2D<unsigned> Vector2u;
  /// @brief Vector 2D of type long.
  typedef Vector2D<long> Vector2l;
  /// @brief Vector 2D of type unsigned long.
  typedef Vector2D<unsigned long> Vector2ul;
  /// @brief Vector 2D of type long long.
  typedef Vector2D<long long> Vector2ll;
  /// @brief Vector 2D of type long long.
  typedef Vector2D<unsigned long long> Vector2ull;
  /// @brief Vector 2D of type Sint8.
  typedef Vector2D<Sint8> Vector2i8;
  /// @brief Vector 2D of type Uint8.
  typedef Vector2D<Uint8> Vector2u8;
  /// @brief Vector 2D of type Sint16.
  typedef Vector2D<Sint16> Vector2i16;
  /// @brief Vector 2D of type Uint16.
  typedef Vector2D<Uint16> Vector2u16;
  /// @brief Vector 2D of type Sint32.
  typedef Vector2D<Sint32> Vector2i32;
  /// @brief Vector 2D of type Uint32.
  typedef Vector2D<Uint32> Vector2u32;
  /// @brief Vector 2D of type Sint64.
  typedef Vector2D<Sint64> Vector2i64;
  /// @brief Vector 2D of type Uint64.
  typedef Vector2D<Uint64> Vector2u64;

} // namespace DPGE

#endif
