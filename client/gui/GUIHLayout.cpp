#include "GUIHLayout.hpp"

GUIHLayout::GUIHLayout(int x, int y, int width, int height, GUILayout *layout)
  : GUILayout(x, y, width, height, layout)
{
}

GUIHLayout::GUIHLayout(int x, int y, int width, int height)
  : GUILayout(x, y, width, height)
{
}

GUIHLayout::~GUIHLayout()
{
}

bool GUIHLayout::handleGUICommand(InputCommand const &command)
{
  if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Left)
    {
      this->prevElement();
      return (true);
    }
  else if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Right)
    {
      this->nextElement();
      return (true);
    }
  return (this->GUILayout::handleGUICommand(command));
}

void GUIHLayout::draw(double elapseTime)
{
  int x = this->_x;
  int y = this->_y;
  for (std::list<GUIElement *>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
      (*it)->draw(x, y, elapseTime);
      x += (*it)->getWidth();
    }
}

void GUIHLayout::draw(int x, int y, double elapseTime)
{
  for (std::list<GUIElement *>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
      (*it)->draw(x, y, elapseTime);
      x += (*it)->getWidth();
    }
}