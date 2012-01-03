#include "CommandHandler.hpp"

CommandHandler::CommandHandler()
{
}

CommandHandler::~CommandHandler()
{
	Command		*command;
	while (!this->_commands.empty())
	{
		command = this->_commands.front();
		this->_commands.pop();
		delete command;
	}
}

bool			CommandHandler::handleCommand(Command &)
{
	return false;
}

bool			CommandHandler::handle(Command &command)
{
	std::list<CommandHandler*>::const_iterator 	it;
	bool										ret = false;

	ret = this->handleCommand(command);
	if (!ret)
	{
		for (it = this->_handlers.begin(); it != this->_handlers.end(); it++)
			return (*it)->handle(command);
	}
	return ret;
}

void			CommandHandler::handle(double)
{
	Command										*command;
	std::list<CommandHandler*>::const_iterator 	it;

	this->_mutex.lock();
	while (!this->_commands.empty())
	{
		command = this->_commands.front();
		this->_commands.pop();
		this->_mutex.unlock();
		for (it = this->_handlers.begin(); it != this->_handlers.end(); it++)
		{
			if ((*it)->handle(*command))
				break ;
		}
		delete command;
		this->_mutex.lock();
	}
	this->_mutex.unlock();
}

void			CommandHandler::pushCommand(Command &command)
{
	Net::ScopedLock		lock(this->_mutex);

	this->_commands.push(&command);
}

void			CommandHandler::registerHandler(CommandHandler &handler)
{
	this->_handlers.push_back(&handler);
}

void			CommandHandler::removeHandler(CommandHandler &handler)
{
	std::list<CommandHandler*>::iterator	it2;

	for (std::list<CommandHandler*>::iterator it = this->_handlers.begin();
		 it != this->_handlers.end();)
	{
		it2 = it++;
		if (*it2 == &handler)
			this->_handlers.erase(it2);
	}
}
