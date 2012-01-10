#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include "Font.hpp"

class SFMLFont : public Font
{
public:
  SFMLFont();
  SFMLFont(std::string const &fileName, std::string const &size);
  ~SFMLFont();

  virtual void	draw(double elapsedTime = 0);
  virtual void	draw(int x, int y, double elapsedTime = 0);
  virtual void	setText(std::string const & text);

private:
  sf::String		_str;
  sf::Font		_font;
  sf::RenderWindow	*_window;
};
