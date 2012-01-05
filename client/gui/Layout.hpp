#pragma once

#include <list>
#include "GUIELement.hpp";

class Layout : public GUIElement
{
public:
  void insertElementAtBegin(GUIElement &elem);
  void insertElementAtEnd(GUIElement &elem);

  bool GUIHandleCommand(Command const &command);

protected:
  Layout();

  std::list<GUIElement *> _elements;
  std::list<GUIElement *>::iterator _focusElement;
};
