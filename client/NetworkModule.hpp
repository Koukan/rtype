#pragma once

#include <string>
#include "Module.hpp"
#include "Net.hpp"
#include "UdpHandler.hpp"
#include "Server.hpp"
#include "Singleton.hpp"
#include "GameCommand.hpp"

class NetworkModule : public Module, public Singleton<NetworkModule>
{
  public:
	NetworkModule();
	virtual ~NetworkModule();
	virtual void		init();
	virtual bool		connect();
	virtual void		update(double elapsedTime);
	virtual void		destroy();
	virtual bool		handleCommand(Command const &command);
	void			setPort(std::string const &port);
	void			setIP(std::string const &ip);
	std::string const	&getPort() const;
	std::string const	&getIP() const;

	void				setServer(Server *server);
  private:

// Command UDP

	void		retrieveCommand(Command const &command);
	void		moveCommand(Command const &command);

// Command TCP

	void		connectionCommand(Command const &command);
	void		createGameCommand(Command const &command);
	void		listGamesCommand(Command const &command);
	void		connectGameCommand(Command const &command);
	void		playerCommand(Command const &command);
		
	void		sendPacketUDP(Net::Packet &packet);

	struct	Method
	{
		std::string	const name;
		void	(NetworkModule::*method)(Command const &);
	};

	Net::Reactor	       	*_reactor;
	Net::Connector<Server>	_connector;
	UdpHandler	       	_udp;
	std::string	       	_port;
	std::string	       	_ip;
	Net::SetupNetwork      	_init;
	Server*				_server;
};
