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

  void updateState(enum ButtonSprite::eState);
  void draw(int x, int y, double elapseTime = 0);
  ButtonSprite *clone() const;

private:
  Sprite	*_defaultSprite;
  Sprite	*_selectedSprite;
  Sprite	*_clickedSprite;
  enum eState	_state;
};
