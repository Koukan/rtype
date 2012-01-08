#include "GUILayout.hpp"

GUILayout::GUILayout(int x, int y, int width, int height, GUILayout *layout)
  : GUIElement(x, y, width, height, layout)
{
  this->_focusElement = this->_elements.begin();
}

GUILayout::GUILayout(int x, int y, int width, int height)
  : GUIElement(x, y, width, height)
{
  this->_focusElement = this->_elements.begin();
}

GUILayout::~GUILayout()
{
}

void GUILayout::focus()
{
  if (this->_focusElement == this->_elements.end())
    this->nextElement();
  this->GUIElement::focus();
}

void GUILayout::unfocus()
{
  if (this->_focusElement != this->_elements.end())
    {
      (*this->_focusElement)->unfocus();
      this->_focusElement = this->_elements.end();
    }
  this->GUIElement::focus();
}

void GUILayout::insertElementAtBegin(GUIElement &elem)
{
  this->_elements.push_front(&elem);
}

void GUILayout::insertElementAtEnd(GUIElement &elem)
{
  this->_elements.push_back(&elem);
}

void GUILayout::prevElement()
{
  if (this->_focusElement != this->_elements.end())
    (*this->_focusElement)->unfocus();
  if (this->_focusElement == this->_elements.begin())
    this->_focusElement = --this->_elements.end();
  else
    --this->_focusElement;
  if (this->_focusElement != this->_elements.end())
    (*this->_focusElement)->focus();
}

void GUILayout::nextElement()
{
  if (this->_focusElement == this->_elements.end())
    this->_focusElement = this->_elements.begin();
  else if (this->_focusElement == --this->_elements.end())
    {
      (*this->_focusElement)->unfocus();
      this->_focusElement = this->_elements.begin();
    }
  else
    {
    (*this->_focusElement)->unfocus();
      ++this->_focusElement;
    }
  if (this->_focusElement != this->_elements.end())
    (*this->_focusElement)->focus();
}

bool GUILayout::handleGUICommand(InputCommand const &command)
{
  if (this->_focusElement != this->_elements.end())
    return ((*(this->_focusElement))->handleGUICommand(command));
  return (false);
}

void		GUILayout::draw(double elapseTime)
{
  for (std::list<GUIElement *>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
      (*it)->draw(elapseTime);
    }
}

void GUILayout::draw(int x, int y, double elapseTime)
{
  for (std::list<GUIElement *>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
      (*it)->draw(x, y, elapseTime);
    }
}
