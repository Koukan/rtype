#include "RendererManager.hpp"
#include "Game.hpp"
#include "RendererManager.hpp"
#include "InputModule.hpp"
#include "PhysicManager.hpp"
#include "GSLoading.hpp"
#include "GSInGame.hpp"
#include "CommandDispatcher.hpp"

Game::Game() : _quit(false)
{
}

Game::~Game()
{
}

void		Game::init()
{
#if defined (YOUPI)
	rgerg;
#endif
  #if defined (WIN32)
  srand(0/*GetTickCount()*/);
  #else
  srand(time(NULL));
  #endif
  ModuleManager::init();
  //cl_log_event("system", "Grab: The Power of the Lost Grapple started");
  this->loadModule(CommandDispatcher::get());
  this->loadModule(RendererManager::get());
  this->loadModule(*(new InputModule));
  this->loadModule(*(new PhysicManager));
// GameStateManager::get().loadState<GSLoading>("Loading");
// GameStateManager::get().changeState("Loading");
  GameStateManager::get().loadState<GSInGame>("Game");
  GameStateManager::get().changeState("Game");
}

void		Game::quit()
{
	this->destroy();
}

