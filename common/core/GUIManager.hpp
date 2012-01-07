#pragma once

#include "GUILayout.hpp"
#include "CommandHandler.hpp"
#include "Singleton.hpp"

class GUIManager : public CommandHandler, public GUILayout
{
public:
  GUIManager();
  ~GUIManager();

  virtual bool		handleCommand(Command &command);
};
