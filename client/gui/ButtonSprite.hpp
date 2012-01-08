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
	       std::string const &buttonClickedSprite,
	       int width = 0, int height = 0);
  ~ButtonSprite();

  void updateState(enum ButtonSprite::eState);
  void draw(int x, int y, double elapseTime = 0);

  int getWidth();
  int getHeight();

private:
  Sprite	*_defaultSprite;
  Sprite	*_selectedSprite;
  Sprite	*_clickedSprite;
  int		_width;
  int		_height;
  enum eState	_state;
};
