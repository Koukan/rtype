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
  virtual void draw(int x, int y, double elapseTime);
  void prevElement();
  void nextElement();

  virtual void focus();
  virtual void unfocus();

protected:
  GUILayout(int x, int y, int width, int height, int padding, GUILayout *layout);
  GUILayout(int x, int y, int width, int height, int padding);
  virtual ~GUILayout();

protected:
  std::list<GUIElement *> _elements;
  std::list<GUIElement *>::iterator _focusElement;
  int _padding;
};
