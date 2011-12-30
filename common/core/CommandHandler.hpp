#pragma once

#include <list>
#include <queue>
#include "Command.hpp"
#include "CommandHandler.hpp"
#include "Mutex.hpp"

class CommandHandler
{
  public:
    CommandHandler();
    virtual ~CommandHandler();
	virtual bool		handleCommand(Command &command);
	bool				handle(Command &command);
	void				handle(double elapsedTime = 0);
	void				pushCommand(Command &command);
	void				registerHandler(CommandHandler &handler);
	void				removeHandler(CommandHandler &handler);

  private:
	std::list<CommandHandler*>	_handlers;
	std::queue<Command*>		_commands;
	Net::Mutex					_mutex;
};
