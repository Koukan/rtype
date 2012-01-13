#pragma once
#include <string>
#include <list>
#include "GameState.hpp"
#include "BulletCommand.hpp"

class GSLoading : public GameState
{
public:
	GSLoading();
	~GSLoading();
	virtual void	onStart();
	virtual	void	update(double elapseTime = 0);

private:
	void			escape(const InputCommand &event);
	void			buttonClick();
	void			listChoice(std::string const &name);

	BulletCommand		*_bullet;
};
