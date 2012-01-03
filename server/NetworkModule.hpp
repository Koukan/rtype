#pragma once

#include <string>
#include "Module.hpp"
#include "Net.hpp"
#include "Player.hpp"

class NetworkModule : public Module
{
  public:
    NetworkModule();
    virtual ~NetworkModule();
	virtual void	init();
	virtual void	update(double elapsedTime);
	virtual void	destroy();
	void			setPort(std::string const &port);

  private:
	Net::Reactor			*_reactor;
	Net::Acceptor<Player>	_acceptor;
	std::string				_port;
	Net::SetupNetwork		_init;
};
