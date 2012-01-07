#include "Layout.hpp"

Layout::Layout(int x, int y, int width, int height, Layout *layout)
  : GUIElement(x, y, width, height, layout)
{
  this->_focusElement = this->_elements.begin();
}

Layout::Layout(int x, int y, int width, int height)
  : GUIElement(x, y, width, height)
{
  this->_focusElement = this->_elements.begin();
}

void Layout::insertElementAtBegin(GUIElement &elem)
{
  this->_elements.push_front(&elem);
}

void Layout::insertElementAtEnd(GUIElement &elem)
{
  this->_elements.push_back(&elem);
}

void Layout::prevElement()
{
  if (this->_focusElement != this->_elements.end())
    (*this->_focusElement)->unfocus();
  if (this->_focusElement == this->_elements.begin())
    this->_focusElement = --(this->_elements.end());
  else
    --this->_focusElement;
  if (this->_focusElement != this->_elements.end())
    (*this->_focusElement)->focus();
}

void Layout::nextElement()
{
  if (this->_focusElement == this->_elements.end())
    this->_focusElement = this->_elements.begin();
  else
    {
    (*this->_focusElement)->unfocus();
      ++this->_focusElement;
    }
  if (this->_focusElement != this->_elements.end())
    (*this->_focusElement)->focus();
}

bool Layout::handleGUICommand(InputCommand const &command)
{
  if (this->_focusElement != this->_elements.end())
    return ((*(this->_focusElement))->handleGUICommand(command));
  return (false);
}

void		Layout::draw(double elapseTime)
{
  for (std::list<GUIElement *>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
      (*it)->draw(elapseTime);
    }
}
