#pragma once

#include "Layout.hpp"
#include "CommandHandler.hpp"
#include "Singleton.hpp"

class GUIManager : public CommandHandler, public Layout
{
public:
  GUIManager();
  ~GUIManager();

  virtual bool		handleCommand(Command &command);
};
