#pragma once

class GameState;

class Command
{
  public:
    Command(std::string const &name) : name(name), state(0)
	{
	}
    virtual ~Command()
	{
	}

	std::string const		name;
	GameState				*state;
};
