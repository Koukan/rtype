#include "Rules.hpp"
#include "BCommand.hpp"
#include "CommandDispatcher.hpp"
#include "GameLogic.hpp"
#include "GameCommand.hpp"

#include <iostream>
void	Rules::wallTouchObject(GameObject &, GameObject &o2)
{
	o2.erase();
}

void		Rules::shotTouchMonster(GameObject&o1, GameObject&o2)
{
	o1.erase();

	std::cout << "jolie collision" << std::endl;
	BCommand &obj = static_cast<BCommand &>(o2);
	obj.setLife(obj.getLife() - 10);
	if (obj.getLife() <= 0)
	{
		GameCommand *cmd = new GameCommand("Destroy");
		cmd->idObject = obj.getId();
		Group *gr = obj.getGroup();
		GameState const &state = gr->getState();
		GameLogic const &gl = static_cast<GameLogic const &>(state);
		cmd->game = &gl.getGame();
		CommandDispatcher::get().pushCommand(*cmd);
		obj.erase();
	}
	
}