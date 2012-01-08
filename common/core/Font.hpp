#pragma once

#include "DrawableObject.hpp"

class Font : public DrawableObject
{
public:
	Font(){}
	virtual ~Font(){}

	virtual void	draw(double /*elapsedTime*/ = 0){}
	virtual void	draw(int /*x*/, int /*y*/, double /*elapsedTime*/ = 0){}
	virtual void	setText(std::string const & /*text*/) {}

protected:
	std::string	_text;
};
