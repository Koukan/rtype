#pragma once

#include "Module.hpp"

class CommandDispatcher : public Module
{
  public:
    CommandDispatcher();
    virtual ~CommandDispatcher();
	virtual void		init();
	virtual void		update(double elapsedTime = 0);
	virtual void		destroy();
};
