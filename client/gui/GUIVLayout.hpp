#pragma once

#include "GUILayout.hpp"

class GUIVLayout : public GUILayout
{
public:
  GUIVLayout(int x, int y, int width, int height, int padding, GUILayout *layout, int nbElements = 100);
  GUIVLayout(int x, int y, int width, int height, int padding, int nbElements = 100);
  ~GUIVLayout();

  virtual void draw(double elapseTime);
  virtual void draw(int x, int y, double elapseTime);

  virtual bool handleGUICommand(InputCommand const &command);
};
