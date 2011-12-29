#pragma once

#include "Command.hpp"

class CommandHandler
{
  public:
    CommandHandler(){}
    virtual ~CommandHandler(){}
	virtual bool		handleCommand(Command &){return false;}
};
