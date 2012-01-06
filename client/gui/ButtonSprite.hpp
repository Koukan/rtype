#pragma once

#include <string>
#include "DrawableObject.hpp"
#include "Sprite.hpp"

class ButtonSprite {
public:
  enum eState {
    DEFAULT,
    SELECTED,
    CLICKED
  };

  ButtonSprite(std::string const &buttonSprite,
	       std::string const &buttonSelectedSprite,
	       std::string const &buttonClickedSprite);
  ~ButtonSprite();

  updateState(enum ButtonSprite::eState);
  draw(int x, int y, double elapseTime = 0);
private:
  Sprite	*_defaultSprite;
  Sprite	*_selectedSprite;
  Sprite	*_clickedSprite;
  enum e_state	_state;
}
