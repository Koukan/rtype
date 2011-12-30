#pragma once

#include <stdint.h>
#include "Sprite.hpp"

class SpriteProvider
{
  public:
    SpriteProvider(){}
    virtual ~SpriteProvider(){}
	virtual Sprite	*addSprite(std::string const &) = 0;
	virtual Sprite	*getSprite(std::string const &) const = 0;
	virtual void	addImage(std::string const &/*path*/, Sprite &) = 0;
};
