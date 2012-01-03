#ifndef		_GAMESTATE_
#define 	_GAMESTATE_

#include <string>
#include "GameObjectManager.hpp"
#include "CommandHandler.hpp"
#include "ResourceManager.hpp"
#include "Command.hpp"
#include "InputManager.hpp"

class Game;

class GameState : public GameObjectManager, public ResourceManager,
		  public CommandHandler
{
public:
  enum Pause
  {
    NONE = 0,
    DRAW = 1,
    PHYSIC = 2,
    ALL = 3
  };

  GameState(const std::string &name);
  virtual ~GameState();
  virtual void	onStart();
  virtual void	onEnd();
  virtual void	onChange();
  virtual void	onResume();
  virtual void	update(double elapseTime = 0);
  void			pause(Pause paused = ALL);
  void			play();
  Pause			getPaused() const;
  InputManager	&getInput();

  const std::string	name;

private:
  Pause			_paused;
  InputManager	_inputManager;
};

#endif		/* _GAMESTATE_ */
