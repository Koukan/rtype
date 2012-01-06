#pragma once

#include "Layout.hpp"

class VLayout : public Layout
{
public:
  VLayout();

  virtual void		draw(double elapseTime);
};
