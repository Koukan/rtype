#pragma once

class GUIElement : public DrawableObject
{
public:
  GUIElement(int x = 0, int y = 0, int width = 0, int height = 0);
  virtual ~GUIElement();

  bool GUIHandleCommand(Command const &command) = 0;
  void focus() = 0;
  void unfocus() = 0;

protected:
  void focus();
  void unfocus();

  bool isFocused;
  int _width;
  int _height;
};
