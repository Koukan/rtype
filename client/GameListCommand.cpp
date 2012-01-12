#include "GameListCommand.hpp"

GameListCommand::GameListCommand(uint16_t idGame, uint8_t nbPlayers, uint8_t state)
  : Command("listGame"), idGame(idGame), nbPlayers(nbPlayers), state(state)
{
}

GameListCommand::~GameListCommand()
{
}
