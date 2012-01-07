#include "GUIElement.hpp"
#include "GUILayout.hpp"
#include "GameStateManager.hpp"

GUIElement::GUIElement(int x, int y, int width, int height, GUILayout *layout)
  : DrawableObject(x, y), _width(width), _height(height)
{
  if (layout)
    layout->insertElementAtEnd(*this);
}

GUIElement::GUIElement(int x, int y, int width, int height)
  : DrawableObject(x, y), _width(width), _height(height)
{
  Singleton<GameStateManager>::get().getCurrentState().getGUI().insertElementAtEnd(*this);
  Singleton<GameStateManager>::get().getCurrentState().getGUI().nextElement();
}

GUIElement::~GUIElement()
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
