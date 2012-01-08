#pragma once

#include "GUIElement.hpp"
#include "ButtonSprite.hpp"
#include <string>

template <typename T>
class GUIButton : public GUIElement
{
public:
  GUIButton(T &instance, void (T::*func)(), std::string const &name, ButtonSprite *sprite, int x, int y, int width, int height)
    : GUIElement(x, y, width, height), _instance(&instance), _func(func)
  {
    if (sprite)
      this->_sprite = new ButtonSprite(*sprite);
    else
      this->_sprite = 0;
  }

  GUIButton(T &instance, void (T::*func)(), std::string const &name, ButtonSprite *sprite, int width, int height, GUILayout *layout)
    : GUIElement(0, 0, width, height, layout), _instance(&instance), _func(func)
  {
    if (sprite)
      this->_sprite = new ButtonSprite(*sprite);
    else
      this->_sprite = 0;
  }

  ~GUIButton()
  {
    delete this->_sprite;
  }

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
    if (this->_sprite)
      this->_sprite->draw(this->_x, this->_y, elapseTime);
  }

  virtual void	draw(int x, int y, double elapseTime)
  {
    if (this->_sprite)
      this->_sprite->draw(x, y, elapseTime);
  }

  virtual void focus()
  {
    if (this->_sprite)
      this->_sprite->updateState(ButtonSprite::SELECTED);
    this->GUIElement::focus();
  }

  virtual void unfocus()
  {
    if (this->_sprite)
      this->_sprite->updateState(ButtonSprite::DEFAULT);
    this->GUIElement::unfocus();
  }

private:
  T *_instance;
  void (T::*_func)();
  ButtonSprite *_sprite;
};
