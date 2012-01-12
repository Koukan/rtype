#pragma once

#include "GUIElement.hpp"
#include "ButtonSprite.hpp"
#include "Font.hpp"
#include "GameStateManager.hpp"
#include <string>

template <typename T>
class GUIButton : public GUIElement
{
public:
  GUIButton(T &instance, void (T::*func)(), std::string const &name, std::string const &font, ButtonSprite const &sprite, int x, int y)
    : GUIElement(x, y, sprite.getWidth(), sprite.getHeight()), _instance(&instance), _func(func), _sprite(ButtonSprite(sprite)), _font(GameStateManager::get().getCurrentState().getFont(font))
  {
    if (this->_font)
      this->_font->setText(name);
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
  }

  GUIButton(T &instance, void (T::*func)(), std::string const &name, std::string const &font, ButtonSprite const &sprite, GUILayout *layout)
    : GUIElement(0, 0, sprite.getWidth(), sprite.getHeight(), layout), _instance(&instance), _func(func), _sprite(ButtonSprite(sprite)), _font(GameStateManager::get().getCurrentState().getFont(font))
  {
    if (this->_font)
      this->_font->setText(name);
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
  }

  ~GUIButton()
  {
    delete this->_font;
  }

  virtual bool handleGUICommand(InputCommand const &command)
  {
    if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Return)
      {
	this->_sprite.updateState(ButtonSprite::CLICKED);
	return (true);
      }
    else if (command.Type == InputCommand::KeyReleased && command.Key.Code == Keyboard::Return)
      {
	if (this->_isFocused)
	  this->_sprite.updateState(ButtonSprite::SELECTED);
	else
	  this->_sprite.updateState(ButtonSprite::DEFAULT);
	(this->_instance->*(this->_func))();
	return (true);
      }
    return (false);
  }

  virtual void	draw(double elapseTime)
  {
      this->_sprite.draw(this->_x, this->_y, elapseTime);
    if (this->_font)
      {
	this->_font->draw(this->_x + (this->_width - this->_font->getWidth()) / 2,
			  this->_y + (this->_height - this->_font->getHeight()) / 2 - 5, elapseTime);
      }
  }

  virtual void	draw(int x, int y, double elapseTime)
  {
      this->_sprite.draw(x, y, elapseTime);
    if (this->_font)
      {
	this->_font->draw(x + (this->_width - this->_font->getWidth()) / 2,
			  y + (this->_height - this->_font->getHeight()) / 2 - 5, elapseTime);
      }
  }

  virtual void focus()
  {
    this->_sprite.updateState(ButtonSprite::SELECTED);
    this->GUIElement::focus();
  }

  virtual void unfocus()
  {
    this->_sprite.updateState(ButtonSprite::DEFAULT);
    this->GUIElement::unfocus();
  }

  Font *getFont() const
  {
    return (this->_font);
  }
  
  void setFont(Font *font)
  {
    this->_font = font;
  }

private:
  T *_instance;
  void (T::*_func)();
  ButtonSprite _sprite;
  Font *_font;
};
