#ifndef		_PHYSICMANAGER_
#define 	_PHYSICMANAGER_

#include "GameState.hpp"
#include "PhysicObject.hpp"
#include "GameStateObserver.hpp"
#include "Singleton.hpp"

class PhysicManager : public GameStateObserver
{
  public:
    PhysicManager();
    virtual ~PhysicManager();
	virtual void	init();
    virtual void	update(double elapsedTime);
	virtual void	destroy();

  private:
    void			move(GameObjectManager::groupsMap const &, double);
    void			collide(GameObjectManager::groupsMap const&,
							GameObjectManager::collisionGroupsMap const&);
};

#endif		/* _PHYSICMANAGER_ */
