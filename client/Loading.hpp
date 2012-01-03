#pragma once
#include <list>
#include "GameState.hpp"
#include "BulletCommand.hpp"

class Loading : public GameState
{
public:
	Loading();
	~Loading();
	virtual void	onStart();
	virtual	void	update(double elapseTime = 0);

private:
	void			escape(const InputCommand &event);
	//void			click(const CL_InputEvent &event);
	void			slowTest(const InputCommand &event);
	void			buttonClick();

	BulletCommand		*_bullet;
};
