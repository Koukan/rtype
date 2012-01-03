#include "Server.hpp"
#include "NetworkModule.hpp"

#define		NBTHREAD	8

Server::Server()
{
}

Server::~Server()
{
}

int			Server::init(std::string const &port)
{
	NetworkModule		*network = new NetworkModule;

	this->ModuleManager::init();
	this->ThreadPool::init(NBTHREAD);
	network->setPort(port);
	this->loadModule(*network);
	this->update(0);
}
