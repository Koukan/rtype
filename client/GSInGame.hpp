#pragma once
#include "GameState.hpp"
#include "BulletCommand.hpp"

class GSInGame : public GameState
{
public:
	GSInGame();
	~GSInGame();
	virtual void	onStart();
	virtual void	onEnd();
	virtual void	update(double elapsedTime);
	virtual bool	handleCommand(Command &command);

private:
	struct Method
	{
	  std::string const &	name;
	  void (GSInGame::*method)(InputCommand const &);
	};

	void		moveUp(InputCommand const &event);
  	void		moveDown(InputCommand const &event);
  	void		moveLeft(InputCommand const &event);
  	void		moveRight(InputCommand const &event);
	void		spawn();
};
