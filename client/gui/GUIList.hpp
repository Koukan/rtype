#pragma once

#include <list>
#include "Label.hpp"
#include "GUIElement.hpp"

template <typename T>
class GUIList : public GUIElement {
public:
  GUIList(T &instance, void (*T::func)(std::string const &), int x = 0, int y = 0, int width = 0, int height = 0);

  void addLabel();
  bool GUIHandleCommand(Command const &command);
  void draw();

private:
  void EventLeft();
  void EventRight();

  std::list<Label*>		_labels;
  std::list<Label*>::iterator	_focusLabel;
};
