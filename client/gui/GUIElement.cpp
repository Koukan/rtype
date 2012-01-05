#include "GUIElement.hpp"

void GUIElement::setX(int x)
{
  this->_x = x;
}

void GUIElement::setY(int y)
{
  this->_y = y;
}

void GUIList::focus()
{
  isFocused = true;
}

void GUIList::unfocus()
{
  isFocused = false;
}
