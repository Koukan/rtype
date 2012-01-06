#include "GUIElement.hpp"

GUIElement(int x = 0, int y = 0, int width = 0, int height = 0)
  : DrawableObject(x, y), _width(width), _height(height)
{
}

~GUIElement()
{
}

void GUIElement::setX(int x)
{
  this->_x = x;
}

void GUIElement::setY(int y)
{
  this->_y = y;
}

void GUIElement::focus()
{
  this->_isFocused = true;
}

void GUIElement::unfocus()
{
  this->_isFocused = false;
}
