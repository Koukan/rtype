#pragma once

#include "GUILayout.hpp"

class GUIHLayout : public GUILayout
{
public:
  GUIHLayout(int x, int y, int width, int height, int padding, GUILayout *layout);
  GUIHLayout(int x, int y, int width, int height, int padding);
  ~GUIHLayout();

  virtual void draw(double elapseTime);
  virtual void draw(int x, int y, double elapseTime);

  virtual bool handleGUICommand(InputCommand const &command);
};
