#pragma once

#include "Layout.hpp"

class VLayout : public Layout
{
public:
  VLayout(int x, int y, int width, int height, Layout *layout);
  VLayout(int x, int y, int width, int height);
  ~VLayout();

  virtual bool handleGUICommand(InputCommand const &command);
};
