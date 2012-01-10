#pragma once

#include <string>
#include "Module.hpp"
#include "Net.hpp"
#include "UdpHandler.hpp"
#include "Player.hpp"
#include "Singleton.hpp"
#include "GameCommand.hpp"

class NetworkModule : public Module, public Singleton<NetworkModule>
{
  public:
	NetworkModule();
	virtual ~NetworkModule();
	virtual void		init();
	virtual void		update(double elapsedTime);
	virtual void		destroy();
	virtual bool		handleCommand(Command const &command);
    void			setPort(std::string const &port);
	void			setIP(std::string const &ip);

  private:

// Command

	void		retrieveCommand(GameCommand const &command);
	void		moveCommand(GameCommand const &command);

	void		sendPacket(Net::Packet &packet);

	struct	Method
	{
		std::string	name;
		void	(NetworkModule::*method)(GameCommand const &);
	};

	Net::Reactor	       	*_reactor;
	Net::Connector<Player>	_connector;
	UdpHandler	       	_udp;
	std::string	       	_port;
	std::string	       	_ip;
	Net::SetupNetwork      	_init;
};
