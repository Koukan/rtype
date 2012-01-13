#include "GameListCommand.hpp"

GameListCommand::GameListCommand(std::string const &name, uint16_t idGame, uint8_t nbPlayers, uint8_t state)
  : Command(name), idGame(idGame), nbPlayers(nbPlayers), state(state)
{
}

GameListCommand::GameListCommand(std::string const &name, uint8_t nbPlayers,
								 std::string const &map)
	: Command(name), nbPlayers(nbPlayers), _map(map)
{}

GameListCommand::GameListCommand(std::string const &name, std::string const &login)
	: Command(name), _login(login)
{}

GameListCommand::~GameListCommand()
{
}
