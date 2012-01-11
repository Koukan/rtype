#pragma once

#include <list>
#include <string>
#include "Command.hpp"
#include "ButtonSprite.hpp"
#include "GUIElement.hpp"

template <typename T>
class GUIList : public GUIElement {
public:
  GUIList(T &instance, void (T::*func)(std::string const &), std::string const & font, ButtonSprite &left_arrow, ButtonSprite &middle_sprite, ButtonSprite &right_arrow, int x, int y)
    : GUIElement(x, y, 0, 0),  _leftArrow(left_arrow), _middleSprite(middle_sprite), _rightArrow(right_arrow), _font(GameStateManager::get().getCurrentState().getFont(font)), _instance(&instance), _func(func)
  {
    this->_focusLabel = this->_labels.begin();
  }

  GUIList(T &instance, void (T::*func)(std::string const &), std::string const & font, ButtonSprite &left_arrow, ButtonSprite &middle_sprite, ButtonSprite &right_arrow, GUILayout *layout)
    : GUIElement(0, 0, left_arrow.getWidth() + middle_sprite.getWidth() + right_arrow.getWidth(), middle_sprite.getHeight(), layout), _leftArrow(left_arrow), _middleSprite(middle_sprite), _rightArrow(right_arrow), _font(GameStateManager::get().getCurrentState().getFont(font)), _instance(&instance), _func(func)
  {
    this->_focusLabel = this->_labels.begin();
  }

  ~GUIList()
  {
    delete this->_font;
  }

  virtual void addLabel(std::string const &label)
  {
    this->_labels.push_back(label);
    if (this->_focusLabel == this->_labels.end())
      this->_focusLabel = this->_labels.begin();
  }

  virtual bool handleGUICommand(InputCommand const &command)
  {
    if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Left)
      {
	this->_leftArrow.updateState(ButtonSprite::CLICKED);
	this->EventLeft();
	(this->_instance->*(this->_func))(*(_focusLabel));
	return (true);
      }
    else if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Right)
      {
	this->_rightArrow.updateState(ButtonSprite::CLICKED);
	this->EventRight();
	(this->_instance->*(this->_func))(*(_focusLabel));
	return (true);
      }
    else if (command.Type == InputCommand::KeyReleased && command.Key.Code == Keyboard::Left)
      {
	if (this->_isFocused)
	  this->_leftArrow.updateState(ButtonSprite::SELECTED);
	else
	  this->_leftArrow.updateState(ButtonSprite::DEFAULT);
	return (true);
      }
    else if (command.Type == InputCommand::KeyReleased && command.Key.Code == Keyboard::Right)
      {
	if (this->_isFocused)
	  this->_rightArrow.updateState(ButtonSprite::SELECTED);
	else
	  this->_rightArrow.updateState(ButtonSprite::DEFAULT);
	return (true);
      }
    return (false);
  }

  virtual void focus()
  {
    this->_leftArrow.updateState(ButtonSprite::SELECTED);
    this->_middleSprite.updateState(ButtonSprite::SELECTED);
    this->_rightArrow.updateState(ButtonSprite::SELECTED);
    this->GUIElement::focus();
  }

  virtual void unfocus()
  {
    this->_leftArrow.updateState(ButtonSprite::DEFAULT);
    this->_middleSprite.updateState(ButtonSprite::DEFAULT);
    this->_rightArrow.updateState(ButtonSprite::DEFAULT);
    this->GUIElement::unfocus();
  }

  virtual void draw(double elapseTime)
  {
    this->_leftArrow.draw(this->_x, this->_y, elapseTime);
    this->_middleSprite.draw(this->_x + this->_leftArrow.getWidth(), this->_y, elapseTime);
    this->_rightArrow.draw(this->_x + this->_middleSprite.getWidth() + this->_leftArrow.getWidth(), this->_y, elapseTime);
    this->_font->setText(*(this->_focusLabel));
    this->_font->draw(this->_x + this->_leftArrow.getWidth(), this->_y, elapseTime);
  }

  virtual void draw(int x, int y, double elapseTime)
  {
    this->_leftArrow.draw(x, y, elapseTime);
    this->_middleSprite.draw(x + this->_leftArrow.getWidth(), y, elapseTime);
    this->_rightArrow.draw(x + this->_middleSprite.getWidth() + this->_leftArrow.getWidth(), y, elapseTime);
    this->_font->setText(*(this->_focusLabel));
    this->_font->draw(this->_x + this->_leftArrow.getWidth(), this->_y, elapseTime);
  }

private:
  void EventLeft()
  {
    if (!this->_labels.size())
      return ;
    if (this->_focusLabel == this->_labels.begin())
      this->_focusLabel = this->_labels.end();
    --this->_focusLabel;
  }

  void EventRight()
  {
    if (!this->_labels.size())
      return ;
    ++this->_focusLabel;
    if (this->_focusLabel == this->_labels.end())
      this->_focusLabel = this->_labels.begin();
  }

  ButtonSprite				_leftArrow;
  ButtonSprite				_middleSprite;
  ButtonSprite				_rightArrow;
  Font *				_font;
  T *					_instance;
  void					(T::*_func)(std::string const &);
  std::list<std::string>		_labels;
  std::list<std::string>::iterator	_focusLabel;
};
