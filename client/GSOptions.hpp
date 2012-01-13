#pragma once

#include "GameState.hpp"

class GSOptions : public GameState
{
public:
  GSOptions();
  ~GSOptions();

  void	onStart();

  void returnMenu();
};
