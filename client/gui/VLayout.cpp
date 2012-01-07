#include "VLayout.hpp"

VLayout::VLayout(int x, int y, int width, int height, Layout *layout)
  : Layout(x, y, width, height, layout)
{
}

VLayout::VLayout(int x, int y, int width, int height)
  : Layout(x, y, width, height)
{
}

VLayout::~VLayout()
{
}

bool VLayout::handleGUICommand(InputCommand const &command)
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
  return (this->Layout::handleGUICommand(command));
}
