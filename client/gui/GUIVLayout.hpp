#pragma once

#include "GUILayout.hpp"

class GUIVLayout : public GUILayout
{
public:
  GUIVLayout(int x, int y, int width, int height, GUILayout *layout);
  GUIVLayout(int x, int y, int width, int height);
  ~GUIVLayout();

  virtual bool handleGUICommand(InputCommand const &command);
};
