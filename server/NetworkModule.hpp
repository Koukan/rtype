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

  private:
	typedef	std::map<uint16_t, std::map<uint32_t, Net::Packet*>>	PacketMem;

	Net::Reactor			*_reactor;
	Net::Acceptor<Player>	_acceptor;
	UdpHandler				_udp;
	std::string				_port;
	Net::SetupNetwork		_init;
	PacketMem				_packets;
};
