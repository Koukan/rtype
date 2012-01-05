#pragma once

class GUIElement
{
public:
  GUIElement(int x = 0, int y = 0, int width = 0, int height = 0);
  virtual ~GUIElement();

  void setX(int x);
  void setY(int y);

protected:
  int _x;
  int _y;
  int _width;
  int _height;
};
