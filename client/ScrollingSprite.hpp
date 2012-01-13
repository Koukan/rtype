#pragma once

#include "DrawableObject.hpp"
#include "Sprite.hpp"
#include <list>
#include <string>

class ScrollingSprite : public DrawableObject
{
public:
  enum eDirection
    {
      HORIZONTAL,
      VERTICAL
    };

  ScrollingSprite(int x, int y, int width, int height, ScrollingSprite::eDirection dir, double speed = 0);
  ~ScrollingSprite();

  void pushSprite(std::string const &spriteName);
  void draw(double elapseTime);
  void setSpeed(int speed);

private:
  int		_width;
  int		_height;
  double	_speed;
  double	_offset;

  std::list<Sprite *> _sprites;
  std::list<Sprite *>::const_iterator _current;
  void (ScrollingSprite::*_scrolling)(int elapseTime);

  void hScrolling(int elapseTime);
  void vScrolling(int elapseTime);
  std::list<Sprite *>::const_iterator nextSprite(std::list<Sprite *>::const_iterator const &it);
  std::list<Sprite *>::const_iterator prevSprite(std::list<Sprite *>::const_iterator const &it);
};
