#include <math.h>
#include "Bullet.hpp"
#include "CircleHitBox.hpp"

Bullet::Bullet(double x, double y, double direction, double speed)
	: PhysicObject(*new CircleHitBox(x, y, 5)), _direction(direction),
		_speed(speed), _sprite(0)
{
  _vx = speed * sin(direction);
  _vy = speed * cos(direction);
}

Bullet::Bullet(ResourceManager &resource, std::string const & sprite,
	       double x, double y, double direction, double speed)
	: PhysicObject(*new RectHitBox(x, y, 5, 5)), _direction(direction),
		_speed(speed), _sprite(0)
{
  try
  {
	this->_sprite = resource.getSprite(sprite);
  }
  catch (...)
  {
	std::cerr << "Sprite \"" << sprite  << "\" not found" << std::endl;
  }
  _vx = speed * sin(direction);
  _vy = speed * cos(direction);
}

Bullet::~Bullet()
{
  delete this->_sprite;
}

void		Bullet::draw(double)
{
	if (this->_sprite)
		this->_sprite->draw(static_cast<int>(this->_x), static_cast<int>(this->_y));
}

void		Bullet::setSprite(ResourceManager &resource, std::string const &name)
{
	this->_sprite = resource.getSprite(name);
}

void		Bullet::setSprite(Sprite *sprite)
{
	this->_sprite = sprite;
}
