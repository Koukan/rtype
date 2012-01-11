#pragma once

#include "GameState.hpp"

class GSCreateMenu : public GameState
{
public:
  GSCreateMenu();
  ~GSCreateMenu();

  void  nbPlayerList(std::string const &nbPlayer);

  void	returnMainMenu();
  void	onStart();

private:
  int	_nbPlayers;
};
