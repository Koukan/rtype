#include "GUIVLayout.hpp"

GUIVLayout::GUIVLayout(int x, int y, int width, int height, int padding, GUILayout *layout, int nbElements)
  : GUILayout(x, y, width, height, padding, layout, nbElements)
{
}

GUIVLayout::GUIVLayout(int x, int y, int width, int height, int padding, int nbElements)
  : GUILayout(x, y, width, height, padding, nbElements)
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

void GUIVLayout::draw(double elapseTime)
{
  int x = this->_x;
  int y = this->_y;
  for (std::list<GUIElement *>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
      (*it)->draw(x - (*it)->getWidth() / 2, y, elapseTime);
      y += (*it)->getHeight() + this->_padding;
    }
}

void GUIVLayout::draw(int x, int y, double elapseTime)
{
  for (std::list<GUIElement *>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
      (*it)->draw(x - (*it)->getWidth() / 2, y, elapseTime);
      y += (*it)->getHeight() + this->_padding;
    }
}
