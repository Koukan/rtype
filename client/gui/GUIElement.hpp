#pragma once

#include "DrawableObject.hpp"

class GUIElement : public DrawableObject
{
public:
  GUIElement(int x = 0, int y = 0, int width = 0, int height = 0);
  virtual ~GUIElement();

  virtual void handleFunction() = 0;

protected:
  void focus();
  void unfocus();

  bool _isFocused;
  int _width;
  int _height;
  bool _focus;
};
