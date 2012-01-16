#include "Rules.hpp"
#include "BCommand.hpp"

void	Rules::wallTouchObject(GameObject &, GameObject &o2)
{
	o2.erase();
}

void		Rules::shotTouchMonster(GameObject&o1, GameObject&o2)
{
	o1.erase();

	BCommand &obj = static_cast<BCommand &>(o2);
	obj.setLife(obj.getLife() - 10);
	if (obj.getLife() <= 0)
		obj.erase();
}