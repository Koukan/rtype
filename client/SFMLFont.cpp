#include "SFMLFont.hpp"
#include "RendererManager.hpp"
#include <sstream>

SFMLFont::SFMLFont()
{
}

SFMLFont::SFMLFont(std::string const &fileName, std::string const &strsize)
  : _window(RendererManager::get().getWindow())
{
  if (strsize != "")
    {
      unsigned int size;
      std::istringstream buffer(strsize);
      buffer >> size;
      this->_font.LoadFromFile(fileName, size);
    }
  else
    this->_font.LoadFromFile(fileName);
  this->_str.SetFont(this->_font);
}

SFMLFont::~SFMLFont()
{
}

void	SFMLFont::draw(double /*elapsedTime*/)
{
  this->_str.Move(this->_x, this->_y);
  this->_window->Draw(this->_str);
}

void	SFMLFont::draw(int x, int y, double /*elapsedTime*/)
{
  this->_str.Move(x, y);
  this->_window->Draw(this->_str);
}

void	SFMLFont::setText(std::string const & text)
{
  this->_str.SetText(text);
}