#pragma once

#include "Command.hpp"

class GameListCommand : public Command
{
public:
  GameListCommand(uint16_t idGame, uint8_t nbPlayers, uint8_t state);
  ~GameListCommand();

  uint16_t	idGame;
  uint8_t	nbPlayers;
  uint8_t	state;
};
