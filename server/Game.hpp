#pragma once

#include "Player.hpp"
#include "Module.hpp"
#include "GameLogic.hpp"

class Game : public Module
{
  public:
    Game(uint16_t id, uint8_t maxPlayers);
    virtual ~Game();
	virtual void	init();
	virtual void	update(double elapsedTime);
	virtual void	destroy();
	void			updateGameState(double elapsedTime);
	bool			addPlayer(Player &player);
	void			removePlayer(Player &player);
	size_t			nbPlayers() const;
	bool			isFull() const;
	uint16_t		getId() const;
	uint8_t			getMaxPlayers() const;
	void			sendTCPPacket(Net::Packet &packet, Player *player = 0);
	void			sendUDPPacket(Net::Packet &packet, Player *player = 0);
	GameLogic		&getGameLogic();
	std::list<Player*> const	&getPlayers() const;

  private:
	void			broadcastStatus(Player &player, int status);
	void			startGame();

	GameLogic			_logic;
	uint16_t			_id;
	uint8_t				_maxPlayers;
	std::list<Player*>	_list;
	friend class GameLogic;
};
