#pragma once

#include <string>

class GameState;

class Command
{
  public:
    Command(std::string const &name) : name(name)
	{
	}
    virtual ~Command()
	{
	}

	std::string const		name;
};
