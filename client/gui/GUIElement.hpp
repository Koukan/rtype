#pragma once

#include "DrawableObject.hpp"
#include "Input.hpp"

class Layout;

class GUIElement : public DrawableObject
{
public:
  GUIElement(int x, int y, int width, int height, Layout *layout);
  GUIElement(int x, int y, int width, int height);
  virtual ~GUIElement();

  virtual bool handleGUICommand(InputCommand const &command) = 0;
  void setX(int x);
  void setY(int y);
  void focus();
  void unfocus();

protected:

  bool _isFocused;
  int _width;
  int _height;
  bool _focus;
};
