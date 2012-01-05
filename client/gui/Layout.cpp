#include "Layout.hpp"

void insertElementAtBegin(GUIElement &elem)
{
  this->_elements.push_front(&elem);
}

void insertElementAtEnd(GUIElement &elem)
{
  this->_elements.push_front(&elem);
}
