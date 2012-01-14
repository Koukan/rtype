#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"
#include "PacketCommand.hpp"
#include "PacketType.hpp"
#include "GameCommand.hpp"

NetworkModule::NetworkModule() : Module("NetworkModule", 20), _reactor(0)
{
	CommandDispatcher::get().registerHandler(*this);
}

NetworkModule::~NetworkModule()
{
}

void		NetworkModule::init()
{
	Net::InetAddr		addr(this->_port);

	this->_reactor = new DefaultSyncPolicy;
	if (this->_acceptor.setup(addr, *this->_reactor) < 0)
	{
		Net::printLastError();
		return ;
	}
	this->_udp.setReactor(*this->_reactor);
	if (_udp.setup(addr) != -1)
		this->_udp.init();
	else
		Net::printLastError();
}

void		NetworkModule::update(double)
{
	if (this->_reactor)
		this->_reactor->waitForEvent(0);
}

void		NetworkModule::destroy()
{
}

bool		NetworkModule::handleCommand(Command const &command)
{
	static Method const	methods[] = {
		{"Spawn", &NetworkModule::spawnCommand},
		{"Destroy", &NetworkModule::destroyCommand},
		{"Move", &NetworkModule::moveCommand},
		{"Status", &NetworkModule::statusCommand},
		{"Startgame", &NetworkModule::startgameCommand},
		{"RangeId", &NetworkModule::rangeId}
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

void		NetworkModule::setPort(std::string const &port)
{
	this->_port = port;
}

void		NetworkModule::addUDPPlayer(Player &player)
{
	Net::InetAddr		addr;

	if (player.getRemoteAddr(addr) != -1)
	{
		_players[addr] = &player;
		this->_udp.addAddr(addr);
	}
}

void		NetworkModule::removeUDPPlayer(Player &player)
{
	Net::InetAddr		addr;

	if (player.getRemoteAddr(addr) != -1)
	{
		_players.erase(addr);
		this->_udp.removeAddr(addr);
	}
}

Player 		*NetworkModule::getPlayerByAddr(Net::InetAddr const &addr) const
{
	std::map<Net::InetAddr, Player *>::const_iterator it = _players.find(addr);

	return ((it != _players.end()) ? it->second : 0);
}

void		NetworkModule::spawnCommand(Command const &command)
{
	GameCommand	const &cmd = static_cast<GameCommand const &>(command);

	std::cout << "spawn" << std::endl;
	if (cmd.game)
	{
		std::cout << "spawn2" << std::endl;
		Net::Packet		packet(29);
		packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
		packet << static_cast<uint8_t>(UDP::SPAWN);
		packet << 0;
		packet << cmd.idResource;
		packet << cmd.idObject;
		packet << cmd.x;
		packet << cmd.y;
		packet << cmd.vx;
		packet << cmd.vy;
		this->sendUDPPacket(packet, cmd.game->getPlayers(),
						 true, cmd.player);
	}
}

void		NetworkModule::destroyCommand(Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);
	if (cmd.game)
	{
		Net::Packet		packet(17);
		packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
		packet << static_cast<uint8_t>(UDP::DESTROY);
		packet << 0;
		packet << cmd.idObject;
		this->sendUDPPacket(packet, cmd.game->getPlayers(),
						 true, cmd.player);
	}
}

void		NetworkModule::moveCommand(Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);
	if (cmd.game)
	{
		Net::Packet		packet(17);
		packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
		packet << static_cast<uint8_t>(UDP::MOVE);
		packet << cmd.idObject;
		packet << cmd.x;
		packet << cmd.y;
		packet << cmd.vx;
		packet << cmd.vy;
		this->sendUDPPacket(packet, cmd.game->getPlayers(),
						 false, cmd.player);
	}
}

void		NetworkModule::sendUDPPacket(Net::Packet &packet,
				std::list<Player*> const &list,
				bool needId, Player *player)
{
	uint32_t	id;

	for (std::list<Player*>::const_iterator it = list.begin();
		 it != list.end(); it++)
	{
		if (player != *it)
		{
			Net::InetAddr		ipaddr;
			if ((*it)->getRemoteAddr(ipaddr) == -1)
				return ;
			ipaddr.setPort(25557);
			if (needId)
			{
				packet.wr_ptr(9);
				id = (*it)->getPacketId();
				packet << id;
				(*it)->addPacket(id, packet);
			}
			packet.setDestination(ipaddr);
			this->_udp.handleOutputPacket(packet);
		}
	}
}

void		NetworkModule::sendTCPPacket(Net::Packet &packet, std::list<Player*> const &list, Player *player)
{	
	for (std::list<Player*>::const_iterator it = list.begin(); it != list.end(); it++)
	{
		if (player == *it)
			continue ;
		(*it)->handleOutputPacket(packet);
	}
}

void        NetworkModule::statusCommand(Command const &command)
{	
	GameCommand const &cmd = static_cast<GameCommand const &>(command);
	
	if (cmd.game)
	{
		Net::Packet	packet(64);

		packet << static_cast<uint8_t>(TCP::PLAYER);
		packet << static_cast<uint16_t>(cmd.idObject);
	   	packet << cmd.player->getName();
		packet << cmd.player->getId();
		this->sendTCPPacket(packet, cmd.game->getPlayers(), cmd.player);
	}
}

void		NetworkModule::startgameCommand(Command const &command)
{	
	GameCommand const &cmd = static_cast<GameCommand const &>(command);
	if (cmd.game)
	{
		Net::Packet	packet(2);

		packet << static_cast<uint8_t>(TCP::GAMESTATE);
		packet << static_cast<uint8_t>(0);
		this->sendTCPPacket(packet, cmd.game->getPlayers(), 0);
	}
}

void		NetworkModule::rangeId(Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);

	if (cmd.player)
	{
		Net::Packet	packet(10);

		packet << static_cast<uint8_t>(TCP::RANGEID);
		packet << static_cast<uint8_t>(cmd.x);
		packet << static_cast<uint32_t>(cmd.idObject);
		packet << static_cast<uint32_t>(cmd.idResource);
		cmd.player->handleOutputPacket(packet);
	}
}
