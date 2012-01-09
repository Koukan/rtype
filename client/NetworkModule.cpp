#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"
#include "PacketCommand.hpp"
#include "PacketType.hpp"

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

void	       	NetworkModule::update(double)
{
	if (this->_reactor)
		this->_reactor->waitForEvent(0);
}

void	       	NetworkModule::destroy(void)
{

}

bool		NetworkModule::handleCommand(Command const &command)
{
	static Method const	methods[] = {
		{"Move", &NetworkModule::moveCommand}
	};

	for (size_t i = 0;
		 i < sizeof(methods) / sizeof(*methods); i++)
	{
		if (command.name == methods[i].name)
		{
			(this->*methods[i].method)(static_cast<GameCommand const &>(command));
			return true;
		}
	}
	return false;
}

void		NetworkModule::moveCommand(GameCommand const &cmd)
{
	Net::Packet		packet(21);
	packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
	packet << static_cast<uint8_t>(UDP::MOVE);
	packet << cmd.idObject;
	packet << cmd.x;
	packet << cmd.y;
	packet << cmd.vx;
	packet << cmd.vy;
	this->sendPacket(packet);
}

void		NetworkModule::retrieveCommand(GameCommand const &cmd)
{
	Net::Packet		packet(13);
	packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
	packet << static_cast<uint8_t>(UDP::RETRIEVE);
	packet << cmd.idObject;
	this->sendPacket(packet);
}

void		NetworkModule::setPort(std::string const &port)
{
	this->_port = port;
}

void		NetworkModule::setIP(std::string const &ip)
{
	this->_ip = ip;
}

void		NetworkModule::sendPacket(Net::Packet &packet)
{
	packet.setDestination(this->_ip);
	this->_udp.handleOutputPacket(packet);
}