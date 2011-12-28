#ifndef		_GAME_
#define 	_GAME_

#include <string>
#include "Singleton.hpp"
#include "GameStateManager.hpp"
#include "ModuleManager.hpp"

class Game : public Singleton<Game>, public ModuleManager
{
public:
  Game();
  virtual ~Game();
  void		init();
  void		quit();

private:
  bool		_quit;
};

#endif		/* _GAME_ */
