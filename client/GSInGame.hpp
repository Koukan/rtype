#pragma once
#include <map>
#include "GameState.hpp"
#include "BulletCommand.hpp"
#include "GameCommand.hpp"
#include "PhysicObject.hpp"

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
	typedef std::map<int, PhysicObject *> GameObjectsMap;

	struct Method
	{
	  std::string const &	name;
	  void (GSInGame::*method)(GameCommand const &);
	};

	void		moveUp(InputCommand const &event);
  	void		moveDown(InputCommand const &event);
  	void		moveLeft(InputCommand const &event);
  	void		moveRight(InputCommand const &event);
	void		destroy(GameCommand const &event);
	void		spawn(GameCommand const &event);
	void		score(GameCommand const &event);
	void		life(GameCommand const &event);
	void		retrieve(GameCommand const &event);
	void		move(GameCommand const &event);

	GameObjectsMap _gameObjects;
};
