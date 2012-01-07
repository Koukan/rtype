#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"
#include "PacketCommand.hpp"

NetworkModule::NetworkModule(void) : Module("NetworkModule", 20), _reactor(0)
{
	CommandDispatcher::get().registerHandler(*this);
}

NetworkModule::~NetworkModule(void)
{

}

void	       	NetworkModule::init(void)
{
	Net::InetAddr		addr(this->_ip, this->_port);

	this->_reactor = new DefaultSyncPolicy;
	this->_connector.setup(addr, *this->_reactor);
	this->_udp.setReactor(*this->_reactor);
	if (this->_udp.setup(addr) != -1)
		this->_udp.init();
}

void	       	NetworkModule::update(double elapsedTime)
{
	if (this->_reactor)
		this->_reactor->waitForEvent(0);
}

void	       	NetworkModule::destroy(void)
{

}

bool		NetworkModule::handleCommand(Command &command)
{
	if (command.name == "TCPPacket")
	{
		PacketCommand &cmd = static_cast<PacketCommand&>(command);
		cmd.player.handleOutputPacket(cmd.packet);
		return true;
	}
	else if (command.name == "UDPPacket")
	{
		PacketCommand &cmd = static_cast<PacketCommand&>(command);
		Net::InetAddr	addr;
		cmd.player.getRemoteAddr(addr);
		cmd.packet.setDestination(addr);
		this->_udp.handleOutputPacket(cmd.packet);
		return true;
	}
	return false;
}

void		NetworkModule::setPort(std::string const &port)
{
	this->_port = port;
}

void		NetworkModule::setIP(std::string const &ip)
{
	this->_ip = ip;
}
