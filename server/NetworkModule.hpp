#pragma once

#include <string>
#include "Module.hpp"
#include "Net.hpp"
#include "Player.hpp"
#include "UdpHandler.hpp"
#include "Singleton.hpp"

class NetworkModule : public Module, public Singleton<NetworkModule>
{
  public:
    NetworkModule();
    virtual ~NetworkModule();
	virtual void	init();
	virtual void	update(double elapsedTime);
	virtual void	destroy();
	virtual bool	handleCommand(Command &command);
	void			setPort(std::string const &port);
	void			addUDPPlayer(Player &player);
	void			removeUDPPlayer(Player &player);
	Player			*getPlayerByAddr(Net::InetAddr const &addr) const;

  private:
	typedef	std::map<uint16_t, std::map<uint32_t, Net::Packet*>>	PacketMem;

	struct	Method
	{
		std::string	name;
		void	(NetworkModule::*method)(Command const &);
	};

	void		spawnCommand(Command const &command);
	void		destroyCommand(Command const &command);
	void		moveCommand(Command const &command);

	void		sendPacket(Net::Packet &packet,
					std::list<Player*> const &list,
					bool needId, Player *player);

	Net::Reactor			*_reactor;
	Net::Acceptor<Player>	_acceptor;
	UdpHandler				_udp;
	std::string				_port;
	Net::SetupNetwork		_init;
	PacketMem				_packets;
	std::map<Net::InetAddr, Player *>		_players;
};
