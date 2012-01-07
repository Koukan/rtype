#pragma once

#include "GUIElement.hpp"
#include "ButtonSprite.hpp"
#include <string>

template <typename T>
class GUIButton : public GUIElement
{
public:
  GUIButton(T &instance, void (T::*func)(), std::string const &name, ButtonSprite &sprite, int x, int y, int width, int height)
    : GUIElement(x, y, width, height), _instance(&instance), _func(func), _sprite(&sprite)
  {
  }

  GUIButton(T &instance, void (T::*func)(), std::string const &name, ButtonSprite &sprite, int width, int height, Layout *layout)
    : GUIElement(0, 0, width, height, layout), _instance(&instance), _func(func), _sprite(&sprite)
  {
  }

  ~GUIButton() {}

  virtual bool handleGUICommand(InputCommand const &command)
  {
    if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Return)
      {
	this->_sprite->updateState(ButtonSprite::CLICKED);
	return (true);
      }
    else if (command.Type == InputCommand::KeyReleased && command.Key.Code == Keyboard::Return)
      {
	if (this->_isFocused)
	  this->_sprite->updateState(ButtonSprite::SELECTED);
	else
	  this->_sprite->updateState(ButtonSprite::DEFAULT);
	(this->_instance->*(this->_func))();
	return (true);
      }
    return (false);
  }

  virtual void	draw(double elapseTime)
  {
    this->_sprite->draw(this->_x, this->_y, elapseTime);
  }
  

private:
  T *_instance;
  void (T::*_func)();
  ButtonSprite *_sprite;
};
