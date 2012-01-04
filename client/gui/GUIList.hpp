#pragma once

#include <list>
#include "Label.hpp"
#include "GUIElement.hpp"

class GUIList : public GUIElement {
private:
  void EventLeft();
  void EventRight();

  std::list<Label*>		labels;
  std::list<Label*>::iterator	focusLabel;
  bool				isFocused;

public:
  GUIList(int x = 0, int y = 0, int width = 0, int height = 0);

  void addLabel();
  bool GUIHandleCommand(Command const &command);
  void focus();
  void unfocus();
  void draw();
};
