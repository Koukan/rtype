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
	void			sendTCPPacket(Net::Packet &packet, Player *player = 0);
	void			sendUDPPacket(Net::Packet &packet, Player *player = 0);
	GameLogic		&getGameLogic();
	std::list<Player*> const	&getPlayers() const;

  private:
	void			sendPacket(std::string const &type,
							   Net::Packet &packet,
							   Player *player);

	GameLogic			&_logic;
	uint16_t			_id;
	uint8_t				_maxPlayers;
	std::list<Player*>	_list;
};
