#include "GUIVLayout.hpp"

GUIVLayout::GUIVLayout(int x, int y, int width, int height, GUILayout *layout)
  : GUILayout(x, y, width, height, layout)
{
}

GUIVLayout::GUIVLayout(int x, int y, int width, int height)
  : GUILayout(x, y, width, height)
{
}

GUIVLayout::~GUIVLayout()
{
}

bool GUIVLayout::handleGUICommand(InputCommand const &command)
{
  if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Up)
    {
      this->prevElement();
      return (true);
    }
  else if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Down)
    {
      this->nextElement();
      return (true);
    }
  return (this->GUILayout::handleGUICommand(command));
}
