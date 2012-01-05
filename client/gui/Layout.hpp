#pragma once

#include <list>

class Layout
{
public:
  void insertElementAtBegin(GUIElement &elem);
  void insertElementAtEnd(GUIElement &elem);

protected:
  Layout();

  std::list<GUIElement *> _elements;
};
