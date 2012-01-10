// herite de physicObject (ctor load sprite auto, draw dessine le sprite), enregistrer le monstre aupres de GameObjectManager

#pragma once

#include <iostream>
#include "PhysicObject.hpp"
#include "ResourceManager.hpp"
#include "Sprite.hpp"
#include "HitBox.hpp"

class Monster : public PhysicObject
{
public:
	Monster(Sprite *sprite, HitBox & hitbox, double vx, double vy);
	virtual ~Monster();
	virtual void draw(double);

private:
	Sprite		*_sprite;
};
