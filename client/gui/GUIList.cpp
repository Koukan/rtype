#include "GUIList.hpp"

GUIList::GUIList()
  : isFocused(false)
{
  focusLabel = labels.begin();
}

void GUIList::addLabel(Label *label)
{
  labels.push_back(label);
  if (focusLabel == NULL)
    focusLabel = label;
}

void GUIList::EventLeft()
{
  if (focusLabel == labels.begin())
    focusLabel = labels.end();
  --focusLabel;
}

void GUIList::EventRight()
{
  ++focusLabel;
  if (focusLabel == labels.end())
    focusLabel = labels.begin();
}

void GUIList::draw()
{
  
}

bool GUIList::GUIHandleCommand(Command const &command)
{
  return true;
}
