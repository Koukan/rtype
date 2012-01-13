#pragma once

#include <list>
#include <string>
#include "Command.hpp"
#include "ButtonSprite.hpp"
#include "GUIElement.hpp"
#include "GUITextBoxCharMap.hpp"

template <typename T>
class GUITextBox : public GUIElement {
public:
  GUITextBox(T &instance, void (T::*func)(std::string const &), std::string const & font, ButtonSprite &sprite, int x, int y)
    : GUIElement(x, y, sprite.getWidth(), sprite.getHeight()), _sprite(sprite), _font(GameStateManager::get().getCurrentState().getFont(font)), _instance(&instance), _func(func), _text("")
  {
  }

  GUITextBox(T &instance, void (T::*func)(std::string const &), std::string const & font, ButtonSprite &sprite, GUILayout *layout)
    : GUIElement(0, 0, sprite.getWidth(), sprite.getHeight(), layout), _sprite(sprite), _font(GameStateManager::get().getCurrentState().getFont(font)), _instance(&instance), _func(func), _text("")
  {
  }

  ~GUITextBox()
  {
    delete this->_font;
  }

  virtual bool handleGUICommand(InputCommand const &command)
  {
    if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Back)
      {
	this->_text = this->_text.substr(0, this->_text.size() - 1);
	(this->_instance->*(this->_func))(this->_text);
	return true;
      }
    if (command.Type == InputCommand::KeyPressed && GUITextBoxCharMap.find(command.Key.Code) != GUITextBoxCharMap.end())
      {
	this->_text += GUITextBoxCharMap[command.Key.Code];
	(this->_instance->*(this->_func))(this->_text);
	return true;
      }
    return false;
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

  virtual void draw(double elapseTime)
  {
    this->_sprite.draw(this->_x, this->_y, elapseTime);
    if (this->_font)
      {
	this->_font->setText(this->_text);
	this->_font->draw(this->_x + ((this->_sprite.getWidth() - this->_font->getWidth()) / 2),
			  this->_y + ((this->_sprite.getHeight() - this->_font->getHeight()) / 2) - 5, elapseTime);
      }
  }

  virtual void draw(int x, int y, double elapseTime)
  {
    this->_sprite.draw(x, y, elapseTime);
    if (this->_font)
      {
	this->_font->setText(this->_text);
	this->_font->draw(x + ((this->_sprite.getWidth() - this->_font->getWidth()) / 2),
			  y + ((this->_sprite.getHeight() - this->_font->getHeight()) / 2) - 5, elapseTime);
      }
  }

private:
  ButtonSprite				_sprite;
  Font *				_font;
  T *					_instance;
  void					(T::*_func)(std::string const &);
  std::string				_text;
};