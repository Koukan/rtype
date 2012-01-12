#include "Ship.hpp"

Ship::Ship(HitBox &hitbox, Player *player) : PhysicObject(hitbox), _player(player)
{}

Ship::~Ship()
{
}
