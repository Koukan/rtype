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

bool Layout::GUIHandleCommand(Command const &command)
{
  //
  /* handle command */
  //

  if (this->_focusElement)
    return (this->_focusElement->GUIHandleCommand(command));
  return (false);
}
