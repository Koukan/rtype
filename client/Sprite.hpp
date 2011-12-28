#pragma once

#include "DrawableObject.hpp"
#include "ResourceManager.hpp"

class Sprite : public DrawableObject
{
public:
	//Sprite(std::string const & fullname, double x = 0, double y = 0);
	//Sprite(std::string const & resource_id, ResourceManager &resources, double x = 0, double y = 0);
	virtual ~Sprite(){}

	virtual void		draw(double elapseTime = 0){}
	virtual void		draw(int x, int y, double elapseTime = 0){}
};
