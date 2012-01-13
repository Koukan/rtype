#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"
#include "GameListCommand.hpp"
#include "PacketCommand.hpp"
#include "PacketType.hpp"

NetworkModule::NetworkModule() : Module("NetworkModule", 20)
{
	CommandDispatcher::get().registerHandler(*this);
}

NetworkModule::~NetworkModule()
{
}

void	    NetworkModule::init()
{
}

bool		NetworkModule::connect()
{
  Net::InetAddr		addr(this->_ip, this->_port);

  if (this->_connector.setup(addr, this->_reactor, false) < 0)
  {
	Net::printLastError();
	return (false);
  }
  Net::InetAddr     tmp(this->_port); 
  this->_udp.close();
  this->_udp.setReactor(this->_reactor);
  if (this->_udp.setup(tmp) != -1)
    {
      this->_udp.init();
      return (true);
    }
  else
	Net::printLastError();
  return (false);
}

void	       	NetworkModule::update(double)
{
	this->_reactor.waitForEvent(0);
}

void	       	NetworkModule::destroy(void)
{
}

bool		NetworkModule::handleCommand(Command const &command)
{
	static Method const	methods[] = {
		{"Connection", &NetworkModule::connectionCommand},
		{"CreateGame", &NetworkModule::createGameCommand},
		{"ListGames", &NetworkModule::listGamesCommand},
		{"ConnectGame", &NetworkModule::connectGameCommand},
		{"Move", &NetworkModule::moveCommand},
		{"Retrieve", &NetworkModule::retrieveCommand},
		{"Player", &NetworkModule::playerCommand}
		/*must be completed */
	};

	for (size_t i = 0;
		 i < sizeof(methods) / sizeof(*methods); i++)
	{
		if (command.name == methods[i].name)
		{
			(this->*methods[i].method)(command);
			return true;
		}
	}
	return false;
}

void		NetworkModule::connectionCommand(Command const &command)
{
	GameListCommand const &cmd = static_cast<GameListCommand const &>(command);
	Net::Packet		packet(sizeof(uint16_t) + sizeof(uint8_t) + cmd._login.length() + 1);

	std::cout << "send connection " << std::endl;
	packet << static_cast<uint16_t>((sizeof(uint8_t) + cmd._login.length() + 1));
	packet << static_cast<uint8_t>(TCP::CONNECTION);
	packet << cmd._login;
	std::cout << cmd._login << std::endl;
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::createGameCommand(Command const &command)
{
	GameListCommand const &cmd = static_cast<GameListCommand const &>(command);
	Net::Packet		packet(sizeof(uint16_t) + sizeof(uint8_t) + sizeof(uint8_t) + cmd._map.length() + 1);

	packet << static_cast<uint16_t>((sizeof(uint8_t) + cmd.name.length() + 1));
	packet << static_cast<uint8_t>(TCP::CREATE_GAME);
	packet << cmd._map;
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::listGamesCommand(Command const &cmd)
{
	Net::Packet		packet(sizeof(uint16_t) + sizeof(uint8_t));

	std::cout << "send list game " << std::endl;
	packet << static_cast<uint16_t>((sizeof(uint8_t)));
	packet << static_cast<uint8_t>(TCP::LIST_GAMES);
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::connectGameCommand(Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);
	Net::Packet		packet(sizeof(uint16_t) + sizeof(uint8_t) + sizeof(uint16_t));
	packet << static_cast<uint16_t>((sizeof(uint8_t) + sizeof(uint16_t)));
	packet << static_cast<uint8_t>(TCP::GAME);
	packet << (static_cast<int16_t>(cmd.idObject)); // idObject represents here idGame
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::playerCommand(Command const &command)
{
	GameListCommand const &cmd = static_cast<GameListCommand const &>(command);
	Net::Packet		packet(sizeof(uint16_t) + sizeof(uint8_t) + sizeof(uint8_t) + cmd._login.length() + 1);

	packet << static_cast<uint16_t>(sizeof(uint8_t) + sizeof(uint8_t) + cmd._login.length() + 1);
	packet << static_cast<uint8_t>(TCP::PLAYER);
	packet << static_cast<uint8_t>(cmd._status);
	packet << cmd._login;
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::moveCommand(Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);
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

void		NetworkModule::retrieveCommand(Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);
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
