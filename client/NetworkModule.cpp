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
	this->_reactor = new DefaultSyncPolicy;
}

bool		NetworkModule::connect()
{
  std::cout << "connect :" << std::endl;
  std::cout << this->_ip << std::endl;

  Net::InetAddr		addr(this->_ip, this->_port);

  this->_connector.setup(addr, *this->_reactor);
  this->_udp.setReactor(*this->_reactor);
  if (this->_udp.setup(addr) != -1)
    {
      this->_udp.init();
      return (true);
    }
  return (false);
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
		{"Connection", &NetworkModule::connectionCommand},
		{"ListGames", &NetworkModule::listGamesCommand},
		{"ConnectGame", &NetworkModule::connectGameCommand},
		{"Move", &NetworkModule::moveCommand},
		{"Retrieve", &NetworkModule::retrieveCommand}
		/*must be completed */
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

void		NetworkModule::connectionCommand(GameCommand const &cmd)
{
	Net::Packet		packet(sizeof(uint16_t) + cmd.name.length() + 1 + sizeof(uint8_t));

	packet << (sizeof(uint8_t) + cmd.name.length() + 1);
	packet << TCP::CONNECTION;
	packet << cmd.name;
	packet << '\0';
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::listGamesCommand(GameCommand const &cmd)
{
	Net::Packet		packet(sizeof(uint16_t) + sizeof(uint8_t));

	packet << (sizeof(uint8_t));
	packet << TCP::LIST_GAMES;
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::connectGameCommand(GameCommand const &cmd)
{
	Net::Packet		packet(sizeof(uint16_t) + sizeof(uint8_t) + sizeof(uint16_t));

	packet << (sizeof(uint8_t) + sizeof(uint16_t));
	packet << TCP::LIST_GAMES;
	packet << (static_cast<int16_t>(cmd.idObject));
	this->_server->handleOutputPacket(packet);
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
	this->sendPacketUDP(packet);
}

void		NetworkModule::retrieveCommand(GameCommand const &cmd)
{
	Net::Packet		packet(13);
	packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
	packet << static_cast<uint8_t>(UDP::RETRIEVE);
	packet << cmd.idObject;
	this->sendPacketUDP(packet);
}

void		NetworkModule::setPort(std::string const &port)
{
	this->_port = port;
}

void		NetworkModule::setIP(std::string const &ip)
{
	this->_ip = ip;
}

std::string const	&NetworkModule::getPort() const
{
  return (this->_port);
}

std::string const	&NetworkModule::getIP() const
{
  return (this->_ip);
}

void		NetworkModule::sendPacketUDP(Net::Packet &packet)
{
	packet.setDestination(this->_ip);
	this->_udp.handleOutputPacket(packet);
}

void		NetworkModule::setServer(Server *server)
{
	_server = server;
}
