#include "SFMLFont.hpp"
#include "RendererManager.hpp"
#include <sstream>

SFMLFont::SFMLFont()
{
}

SFMLFont::SFMLFont(std::string const &fileName, std::string const &strsize)
  : _window(RendererManager::get().getWindow())
{
  this->_font.LoadFromFile(fileName);
  this->_str.SetFont(this->_font);
  if (strsize != "")
    {
      unsigned int size;
      std::istringstream buffer(strsize);
      buffer >> size;
      this->_str.SetSize(size);
    }
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
  this->_str.SetX(x);
  this->_str.SetY(y);
  this->_window->Draw(this->_str);
}

void	SFMLFont::setText(std::string const & text)
{
  this->_str.SetText(text);
}
