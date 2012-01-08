#pragma once

#include "GUILayout.hpp"

class GUIVLayout : public GUILayout
{
public:
  GUIVLayout(int x, int y, int width, int height, GUILayout *layout);
  GUIVLayout(int x, int y, int width, int height);
  ~GUIVLayout();

  virtual void draw(double elapseTime);
  virtual void draw(int x, int y, double elapseTime);

  virtual bool handleGUICommand(InputCommand const &command);
};
