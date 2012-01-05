#include "VLayout.hpp"

VLayout::VLayout()
{
}

void VLayout::pressUp()
{
  if (this->_focusElement == this->_elements.begin())
    this->_focusElement = --(this->_elements.end());
  else
    --this->_focusElement;
}

void VLayout::pressDown()
{
  if (this->_focusElement == --(this->_elements.end()))
    this->_focusElement = this->_elements.begin();
  else
    ++this->_focusElement;
}
