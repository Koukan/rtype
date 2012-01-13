#pragma once

#include "GUIButton.hpp"

class GameButton : public GUIButton<GameButton>
{
public:
  GameButton(int id, std::string const &name, ButtonSprite const &sprite, GUILayout *layout);
  ~GameButton();

  void push();

private:
  int _id;
};
