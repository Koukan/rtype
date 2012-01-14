#include "GameButton.hpp"
#include "GameStateManager.hpp"
#include "CommandDispatcher.hpp"
#include "GSLoading.hpp"
#include "GameCommand.hpp"

GameButton::GameButton(int id, std::string const &name, ButtonSprite const &sprite, GUILayout *layout)
  : GUIButton<GameButton>(*this, &GameButton::push, name, "listGameFont", sprite, layout), _id(id)
{
}

GameButton::~GameButton()
{
}

void GameButton::push()
{
  GameCommand *command = new GameCommand("ConnectGame");
  command->idObject = this->_id;

  CommandDispatcher::get().pushCommand(*command);
  GameStateManager::get().loadState<GSLoading>("loading");
  GameStateManager::get().pushState("loading");
}
