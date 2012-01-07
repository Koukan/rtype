#pragma once

#include "DrawableObject.hpp"
#include "Input.hpp"

class GUILayout;

class GUIElement : public DrawableObject
{
public:
  GUIElement(int x, int y, int width, int height, GUILayout *layout);
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
