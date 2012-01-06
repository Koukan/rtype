#pragma once

#include <list>
#include "GUIELement.hpp"

class Layout : public GUIElement
{
public:
  void insertElementAtBegin(GUIElement &elem);
  void insertElementAtEnd(GUIElement &elem);

  virtual void handleFunction();

protected:
  Layout();

  void pressUp();
  void pressDown();

protected:
  std::list<GUIElement *> _elements;
  std::list<GUIElement *>::iterator _focusElement;
};
