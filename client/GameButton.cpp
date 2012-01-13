#include "GameButton.hpp"

GameButton::GameButton(int id, std::string const &name, ButtonSprite const &sprite, GUILayout *layout)
  : GUIButton<GameButton>(*this, &GameButton::push, name, "buttonFont", sprite, layout), _id(id)
{
}

GameButton::~GameButton()
{
}

#include <iostream>
void GameButton::push()
{
  std::cout << "create game " << this->_id << std::endl;
}
