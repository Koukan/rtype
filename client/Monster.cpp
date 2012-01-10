#include "Monster.hpp"

Monster::Monster(Sprite *sprite, HitBox &hitbox, double vx, double vy)
	: PhysicObject(hitbox, vx, vy), _sprite(sprite)
{
}

Monster::~Monster()
{

}

void			Monster::draw(double time)
{
	this->draw(time);
}