#include "RendererManager.hpp"
#include "Game.hpp"
#include "RendererManager.hpp"
#include "InputModule.hpp"
#include "PhysicManager.hpp"
#include "GSLoading.hpp"
#include "GSInGame.hpp"
#include "GSMainMenu.hpp"
#include "CommandDispatcher.hpp"
#include "Net.hpp"
#include "NetworkModule.hpp"

Game::Game() : _quit(false)
{
}

Game::~Game()
{
}

void		Game::init()
{
  srand(Net::Clock::getMsSinceEpoch());
  ModuleManager::init();
  //cl_log_event("system", "Grab: The Power of the Lost Grapple started");
  this->loadModule(CommandDispatcher::get());
  this->loadModule(RendererManager::get());
  this->loadModule(*(new InputModule));
  this->loadModule(*(new PhysicManager));
  this->loadModule(GameStateManager::get());
  this->loadModule(NetworkModule::get());
  CommandDispatcher::get().registerHandler(GameStateManager::get());
  GameStateManager::get().loadState<GSMainMenu>("mainMenu");
  GameStateManager::get().pushState("mainMenu");
  //  GameStateManager::get().loadState<GSInGame>("Game");
  //  GameStateManager::get().pushState("Game");
}

void		Game::quit()
{
	this->destroy();
}

