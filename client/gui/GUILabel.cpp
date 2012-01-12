#include "GUILabel.hpp"

GUILabel::GUILabel(std::string const &name, std::string const &font, ButtonSprite const &sprite, int x, int y)
  : GUIElement(x, y, sprite.getWidth(), sprite.getHeight()), _sprite(sprite), _font(GameStateManager::get().getCurrentState().getFont(font))
{
  if (this->_font)
    this->_font->setText(name);
  this->setEnable(false);
}

GUILabel::GUILabel(std::string const &name, std::string const &font, ButtonSprite const &sprite, GUILayout *layout)
  : GUIElement(0, 0, sprite.getWidth(), sprite.getHeight(), layout), _sprite(sprite), _font(GameStateManager::get().getCurrentState().getFont(font))
{
  if (this->_font)
    this->_font->setText(name);
  this->setEnable(false);
}

GUILabel::~GUILabel()
{
  delete this->_font;
}

bool	GUILabel::handleGUICommand(InputCommand const &)
{
  return (false);
}

void	GUILabel::draw(double elapseTime)
{
  this->_sprite.draw(this->_x, this->_y, elapseTime);
  if (this->_font)
    {
      this->_font->draw(this->_x + (this->_width - this->_font->getWidth()) / 2,
			this->_y + (this->_height - this->_font->getHeight()) / 2 - 5, elapseTime);
    }
}

void	GUILabel::draw(int x, int y, double elapseTime)
{
  this->_sprite.draw(x, y, elapseTime);
  if (this->_font)
    {
      this->_font->draw(x + (this->_width - this->_font->getWidth()) / 2,
			y + (this->_height - this->_font->getHeight()) / 2 - 5, elapseTime);
    }
}

void	GUILabel::setText(std::string const &str)
{
  if (this->_font)
    this->_font->setText(str);
}
