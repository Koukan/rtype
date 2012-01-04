#include "GUIList.hpp"

GUIList::GUIList()
  : focusLabel(NULL), isFocused(false)
{
}

void GUIList::addLabel(Label *label)
{
  labels.push_back(label);
  if (focusLabel == NULL)
    focusLabel = label;
}

void GUIList::EventLeft()
{
  
}

void GUIList::EventRight()
{
}

void GUIList::draw()
{
  
}

void GUIList::focus()
{
  isFocused = true;
}

void GUIList::unfocus()
{
  isFocused = false;
}

bool GUIList::GUIHandleCommand(Command const &command)
{
  return true;
}
