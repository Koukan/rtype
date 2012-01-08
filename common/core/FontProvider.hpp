#pragma once

#include "Font.hpp"

class FontProvider
{
  public:
	FontProvider(){}
	virtual ~FontProvider(){}
	virtual Font	*addFont(std::string const &) = 0;
	virtual Font	*getFont(std::string const &) const = 0;
};
