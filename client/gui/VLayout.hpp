#pragma once

#include "Layout.hpp"

class VLayout : public Layout
{
public:
  VLayout();
private:
  void pressUp();
  void pressDown();
};
