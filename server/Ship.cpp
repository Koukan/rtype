#include "RectHitBox.hpp"
#include "Ship.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"

Ship::Ship(double x, double y, Player *player) : PhysicObject(*new RectHitBox(x, y, 10, 10)), _player(player)
{
	GameCommand	*cmd = new GameCommand("Spawn");
	cmd->idResource = 0;
	cmd->idObject = this->_id;
	cmd->x = this->_x;
	cmd->y = this->_y;
	cmd->vx = this->_vx;
	cmd->vy = this->_vy;
	cmd->game = &player->getGameLogic().getGame();
	CommandDispatcher::get().pushCommand(*cmd);
}

Ship::~Ship()
{
}
