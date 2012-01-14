#pragma once
#include <map>
#include <vector>
#include "GameState.hpp"
#include "BulletCommand.hpp"
#include "GameCommand.hpp"
#include "PhysicObject.hpp"
#include "Font.hpp"
#include "Resources.hpp"

class GSInGame : public GameState
{
public:
	GSInGame();
	~GSInGame();
	virtual void	onStart();
	virtual void	onEnd();
	virtual void	update(double elapsedTime = 0);
	virtual bool	handleCommand(Command const &command);
	void			preload();

private:

	struct Method
	{
	  std::string const		name;
	  void (GSInGame::*method)(GameCommand const &);
	};

	struct Method2
	{
	  Resource::type		type;
	  void (GSInGame::*method)(GameCommand const &);
	};

	void		inputEscape(InputCommand const &event);
	void		inputSpace(InputCommand const &event);
	void		inputUp(InputCommand const &event);
 	void		inputDown(InputCommand const &event);
  	void		inputLeft(InputCommand const &event);
  	void		inputRight(InputCommand const &event);

	// HandleCommand
//	void		inputMove(GameCommand const &event);

	void		destroy(GameCommand const &event);
	void		spawn(GameCommand const &event);
	void		score(GameCommand const &event);
	void		life(GameCommand const &event);
	void		move(GameCommand const &event);
	void		rangeid(GameCommand const &event);

	void		retrieve(uint32_t idPacket);

  //	void		moveObject(InputCommand const &event, int16_t x, int16_t y, int16_t vx, int16_t vy);
  	void		throwShip();

	void		updatePositions(GameCommand const &event, PhysicObject &obj) const;

	void		loadP1(GameCommand const &event);
	void		loadP2(GameCommand const &event);
	void		loadP3(GameCommand const &event);
	void		loadP4(GameCommand const &event);
	void		loadMonster(GameCommand const &event);

	uint32_t	_idPlayer;
	std::vector<uint32_t> _scores;
	std::vector<Font*>    _scoreFonts;
	PhysicObject	*_ship;
};
