#pragma once

#include "GameState.hpp"

class GSJoinGame : public GameState
{
public:
  GSJoinGame();
  ~GSJoinGame();

  void	onStart();
  void	returnMainMenu();
  bool	handleCommand(Command const &command);

private:
  GUILayout *_layout;
  ButtonSprite const *_sprite;
};
