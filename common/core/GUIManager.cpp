#include "GUIManager.hpp"
//#include "GameStateManager.hpp"

GUIManager::GUIManager()
  : GUILayout(0, 0, 0, 0, 0)
{
  //  Singleton<GameStateManager>::get().addGameObject(this);
}

GUIManager::~GUIManager()
{
}

bool		GUIManager::handleCommand(Command &command)
{
  if (command.name == "Input")
    return (this->handleGUICommand(static_cast<InputCommand&>(command)));
  return (false);
}
