#include "ScrollingSprite.hpp"
#include "GameStateManager.hpp"

ScrollingSprite::ScrollingSprite(int x, int y, int width, int height, ScrollingSprite::eDirection dir, double speed)
  : DrawableObject(x, y), _width(width), _height(height), _speed(speed), _dir(dir)
{
}

ScrollingSprite::~ScrollingSprite()
{
  for (std::list<Sprite *>::iterator it = this->_sprites.begin(); it != this->_sprites.end(); ++it)
    delete *it;
}

void ScrollingSprite::pushSprite(std::string const &spriteName)
{
  GameState &gameState = GameStateManager::get().getCurrentState();

  this->_sprites.push_back(gameState.getSprite(spriteName));
  if (this->_sprites.size() == 1)
    this->_current = this->_sprites.begin();
}

void ScrollingSprite::draw(double elapseTime)
{
  std::list<Sprite *>::const_iterator it = this->_current;
  static double x = 0;
  int x2 = x;

  while (x2 < this->_width)
    {
      (*it)->draw(x2 + this->_x, this->_y, elapseTime);
      it = this->nextSprite(it);
      x2 += (*it)->getWidth();
    }
  x += this->_speed * elapseTime;
  if (x + (*this->_current)->getWidth() < 0)
    {
      while (x + (*this->_current)->getWidth() < 0)
	{
	  this->_current = this->nextSprite(this->_current);
	  x += (*this->_current)->getWidth();
	}
    }
  else if (x > 0)
    {
      while (x > 0)
	{
	  this->_current = this->prevSprite(this->_current);
	  x -= (*this->_current)->getWidth();
	}
    }
}

void ScrollingSprite::setSpeed(int speed)
{
  this->_speed = speed;
}

std::list<Sprite *>::const_iterator ScrollingSprite::nextSprite(std::list<Sprite *>::const_iterator const &it)
{
  if (it == --this->_sprites.end())
    return (this->_sprites.begin());

  std::list<Sprite *>::const_iterator tmp = it;
  return (++tmp);
}

std::list<Sprite *>::const_iterator ScrollingSprite::prevSprite(std::list<Sprite *>::const_iterator const &it)
{
  if (it == this->_sprites.begin())
    return (--this->_sprites.end());

  std::list<Sprite *>::const_iterator tmp = it;
  return (--tmp);
}
