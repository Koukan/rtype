#pragma once

#include <list>
#include "GUIElement.hpp"

class GUILayout : public GUIElement
{
public:
  void insertElementAtBegin(GUIElement &elem);
  void insertElementAtEnd(GUIElement &elem);

  virtual bool handleGUICommand(InputCommand const &command);
  virtual void draw(double elapseTime);
  void prevElement();
  void nextElement();

protected:
  GUILayout(int x, int y, int width, int height, GUILayout *layout);
  GUILayout(int x, int y, int width, int height);

protected:
  std::list<GUIElement *> _elements;
  std::list<GUIElement *>::iterator _focusElement;
};
