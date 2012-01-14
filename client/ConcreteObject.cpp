#include "ConcreteObject.hpp"

ConcreteObject::ConcreteObject(Sprite *sprite, HitBox &hitbox, double vx, double vy)
  : PhysicObject(hitbox, vx, vy), _sprite(sprite)
{
}

ConcreteObject::~ConcreteObject()
{
}

void			ConcreteObject::draw(double time)
{
  this->_sprite->setX(this->_x);
  this->_sprite->setY(this->_y);
  this->_sprite->draw(time);
}
