#include "GUIVLayout.hpp"

GUIVLayout::GUIVLayout(int x, int y, int width, int height, int padding, GUILayout *layout)
  : GUILayout(x, y, width, height, padding, layout)
{
}

GUIVLayout::GUIVLayout(int x, int y, int width, int height, int padding)
  : GUILayout(x, y, width, height, padding)
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

#include <iostream>
void GUIVLayout::draw(double elapseTime)
{
  int x = this->_x;
  int y = this->_y;
  std::cout << "youpi" << std::endl;
  for (std::list<GUIElement *>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
      (*it)->draw(x, y, elapseTime);
      y += (*it)->getHeight() + this->_padding;
    }
}

void GUIVLayout::draw(int x, int y, double elapseTime)
{
  for (std::list<GUIElement *>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
      (*it)->draw(x, y, elapseTime);
      y += (*it)->getHeight() + this->_padding;
    }
}
