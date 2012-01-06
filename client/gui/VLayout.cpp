#include "VLayout.hpp"

VLayout::VLayout()
{
}

virtual void		VLayout::draw(double elapseTime)
{
  for (std::list<GUIElement *>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
      *(it)->draw();
    }
}
