#include "Server.hpp"
#include "NetworkModule.hpp"

Server::Server()
{
}

Server::~Server()
{
}

int			Server::init(std::string const &port, size_t nbthread)
{
	NetworkModule		&network = NetworkModule::get();

	this->ModuleManager::init();
	this->ThreadPool::init(nbthread);
	network.setPort(port);
	this->loadModule(network);
	this->update(0);
}
