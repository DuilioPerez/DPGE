/// @file TextureManager.hpp
/// @author Duilio Pérez
/// @brief A class to render textures.
#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP true
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>

namespace DPGE
{

  /// @brief Quality to render text.
  enum struct TextQuality : unsigned
  {
    /// @brief High quality.
    BLENDED,
    /// @brief High quality text, with background.
    LCD,
    /// @brief Medium text, but with background.
    SHADED,
    /// @brief Low quality.
    SOLID
  };

  /// @brief An structure to hold the information of a
  /// texture.
  struct TextureInfo
  {
    /// @brief The name of the texture.
    std::string name;
    /// @brief The source area.
    SDL_Rect *src;
    /// @brief The destination area.
    SDL_Rect *dest;
  };

  /// @brief A structure to hold information of a texture
  /// with single floating point rendering precision.
  struct FTextureInfo
  {
    /// @brief The texture's name.
    std::string name;
    /// @brief Source area.
    SDL_Rect *src;
    /// @brief Destination area.
    SDL_FRect *dest;
  };

  /// @brief The texture manager of the game.
  class TextureManager final
  {
  public:
    /// @brief Copy constructor deleted.
    TextureManager(const TextureManager &) = delete;
    /// @brief Open a font to render text.
    /// @param path The file path of the font.
    /// @param size the size in points of the font.
    /// @return true in success, false otherwise.
    bool openFont(const std::string &path, int size);
    /// @brief Load a texture from a file.
    /// @param name The name or id of the texture.
    /// @param path The path of the file.
    /// @return true in success, false otherwise.
    bool loadFromFile(
      const std::string &name, const std::string &path);
    /// @brief Load a texture from a utf-8 text.
    /// @param name The id of the texture.
    /// @param text The text to render.
    /// @return true in success, false otherwise.
    bool loadFromText(
      const std::string &name, const std::string &text);
    /// @brief Create a texture from a text.
    /// @param name The name of the texture.
    /// @param text The text to render.
    /// @param width The width of text wrap, 0 to wrap only
    /// at newlines.
    /// @return true in success, false otherwise.
    bool loadFromText(const std::string &name,
      const std::string &text, Uint32 width);
    /// @brief Render a texture.
    /// @param name The id of the texture.
    /// @param src The source area.
    /// @param dest The destination area.
    /// @param angle The rotation angle.
    /// @param center The rotation center of the texture,
    /// nullptr to set it at the center of the texture.
    /// @param flip The flip direction.
    /// @return true in success, false otherwise.
    bool render(const std::string &name,
      const SDL_Rect *src, const SDL_Rect *dest,
      double angle = 0, const SDL_Point *center = nullptr,
      const SDL_RendererFlip &flip = SDL_FLIP_NONE);
    /// @brief render a texture using a source and
    /// destination area.
    /// @param name The name of the texture.
    /// @param src The source rectangle.
    /// @param dest The destination rectangle.
    /// @return true in success, false otherwise.
    bool render(const std::string &name,
      const SDL_Rect &src, const SDL_Rect &dest);
    /// @brief Render a texture using a destination
    /// rectangle.
    /// @param name The name of the texture.
    /// @param dest The dest area.
    /// @return true in success, false otherwise.
    bool render(
      const std::string &name, const SDL_Rect &dest);
    /// @brief Render a texture at a given location.
    /// @param name The name of the texture.
    /// @param x The x coordinate.
    /// @param y The y coordinate.
    /// @return true in success, false otherwise.
    bool render(const std::string &name, int x, int y);
    /// @brief Render a texture with single-floating
    /// presicion.
    /// @param name The id of the texture.
    /// @param src The source area.
    /// @param dest The destination area.
    /// @param angle The rotation angle.
    /// @param center The rotation center of the texture,
    /// nullptr to set it at the center of the texture.
    /// @param flip The flip direction.
    /// @return true in success, false otherwise.
    bool render(const std::string &name,
      const SDL_Rect *src, const SDL_FRect *dest,
      double angle = 0, const SDL_FPoint *center = nullptr,
      const SDL_RendererFlip &flip = SDL_FLIP_NONE);
    /// @brief render a texture using a source and
    /// destination area with sngle foating precision.
    /// @param name The name of the texture.
    /// @param src The source rectangle.
    /// @param dest The destination rectangle.
    /// @return true in success, false otherwise.
    bool render(const std::string &name,
      const SDL_Rect &src, const SDL_FRect &dest);
    /// @brief Render a texture using a destination
    /// rectangle with single-floating presicion.
    /// @param name The name of the texture.
    /// @param dest The dest area.
    /// @return true in success, false otherwise.
    bool render(
      const std::string &name, const SDL_FRect &dest);
    /// @brief Render a text.
    /// @param text The text to render.
    /// @param dest The destination coordinates.
    /// @param angle The rotation angle.
    /// @param center The rotation center of the texture,
    /// nullptr to set it at the center of the texture.
    /// @param flip The flip direction.
    /// @return true in success, false otherwise.
    bool renderText(const std::string &text,
      const SDL_Point &dest, double angle = 0,
      const SDL_Point        *center = nullptr,
      const SDL_RendererFlip &flip   = SDL_FLIP_NONE);
    /// @brief Render a text with single floating presicion.
    /// @param text The text to render.
    /// @param dest The destination coordinates.
    /// @param angle The rotation angle.
    /// @param center The rotation center of the texture,
    /// nullptr to set it at the center of the texture.
    /// @param flip The flip direction.
    /// @return true in success, false otherwise.
    bool renderText(const std::string &text,
      const SDL_FPoint &dest, double angle = 0,
      const SDL_FPoint       *center = nullptr,
      const SDL_RendererFlip &flip   = SDL_FLIP_NONE);
    /// @brief Render a text.
    /// @param text The text to render.
    /// @param x The x coordinate
    /// @param y The y coordinate.
    /// @return true in success, false otherwise.
    bool renderText(const std::string &text, int x, int y);
    /// @brief Render a wrapped text
    /// @param text The text to render.
    /// @param x The x coordinate.
    /// @param y The y coordinate.
    /// @param width The maximun width of the text, 0 to
    /// wrap at newlines.
    /// @return true in success or false otherwise.
    bool renderText(
      const std::string &text, int x, int y, Uint32 width);
    /// @brief Present in the window the scene.
    void present();
    /// @brief Change the font used to render text.
    /// @param path The path of the font.
    /// @param size The size of the font in dots.
    /// @return true in success, false otherwise.
    bool changeFont(const std::string &font, int size);
    /// @brief Change the font size.
    /// @param The font size in dots.
    /// @return true in success, false otherwise.
    bool changeFontSize(int size);
    /// @brief Erase a texture.
    /// @param name The id of the texture.
    void erase(const std::string &name);
    /// @brief Delete all the textures.
    void clear();
    /// @brief Set the text rendering quality.
    /// @param quality The quality of the text.
    void setTextQuality(const TextQuality &quality);
    /// @brief Get the text rendering quality.
    /// @return The current text rendering quality.
    const TextQuality &getTextQuality();
    /// @brief Set the foreground color.
    /// @param color The new foreground color.
    void setForegroundColor(const SDL_Color &color);
    /// @brief Get the current foreground color.
    /// @return The current foreground color.
    const SDL_Color &getForegroundColor();
    /// @brief Set the background color.
    /// @param color The new background color.
    void setBackgroundColor(const SDL_Color &color);
    /// @brief Get the current background color.
    /// @return The current background color.
    const SDL_Color &getBackgroundColor();
    /// @brief Get a texture.
    /// @param name The name of the texture.
    const SDL_Texture *getTexture(const std::string &name);
    /// @brief Get a texture to modify it.
    /// @param name The id of the texture.
    SDL_Texture *getModifiableTexture(
      const std::string &name);
    /// @brief Get the instance of the class.
    static TextureManager &getInstance();
    /// @brief Copy operator deleted.
    const TextureManager &operator=(
      const TextureManager &) = delete;

  private:
    /// @brief Default constructor.
    TextureManager() = default;
    /// @brief The textures.
    std::map<const std::string, SDL_Texture *> textures;
    /// @brief The font to render text.
    TTF_Font *font = nullptr;
    /// @brief Current rendering text quality.
    TextQuality textRenderingQuality = TextQuality::SOLID;
    /// @brief Foreground text color.
    SDL_Color foregroundTextColor = {0, 0, 0, 255};
    /// @brief Background text color.
    SDL_Color backgroundTextColor = {255, 255, 255, 255};
  };

  /// @brief The texture manager instance.
  extern TextureManager &theTextureManager;

} // namespace DPGE

#endif
