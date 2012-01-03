#include "NetworkModule.hpp"

NetworkModule::NetworkModule() : Module("NetworkModule", 20), _reactor(0)
{
}

NetworkModule::~NetworkModule()
{
}

void		NetworkModule::init()
{
	Net::InetAddr		addr(this->_port);

	this->_reactor = new DefaultSyncPolicy;
	this->_acceptor.setup(addr, *this->_reactor);
}

void		NetworkModule::update(double)
{
	if (this->_reactor)
		this->_reactor->waitForEvent(0);
}

void		NetworkModule::destroy()
{
}

void		NetworkModule::setPort(std::string const &port)
{
	this->_port = port;
}
