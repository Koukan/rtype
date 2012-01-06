#include "Layout.hpp"

Layout::Layout()
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

void Layout::pressUp()
{
  if (this->_focusElement == this->_elements.begin())
    this->_focusElement = --(this->_elements.end());
  else
    --this->_focusElement;
}

void Layout::pressDown()
{
  if (this->_focusElement == --(this->_elements.end()))
    this->_focusElement = this->_elements.begin();
  else
    ++this->_focusElement;
}

void Layout::handleFunction()
{
  if (this->_focusElement != this->_elements.end())
    {
      *(this->_focusElement)->handleFunction();
    }
}
