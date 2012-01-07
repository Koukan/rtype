#include "GUIManager.hpp"

GUIManager::GUIManager()
  : Layout(0, 0, 0, 0, 0)
{
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
