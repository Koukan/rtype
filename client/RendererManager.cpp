#if defined (_WIN32)
#include <windows.h>
#endif
#include "RendererManager.hpp"
#include "GameStateManager.hpp"
#include "DrawableObject.hpp"
#include "Game.hpp"

RendererManager::RendererManager() : GameStateObserver("RendererManager")
{
	this->_targetRate = 20;
	Game::get().loadModule(*this);
	this->_window = 0;
}

RendererManager::~RendererManager()
{
}

void				RendererManager::init()
{
	this->_width = 1024;
	this->_height = 768;
}

void				RendererManager::update(double elapsedTime)
{
	//GameObjectManager::groupsDisplay::const_iterator	lit;
	//Group::gameObjectSet::const_iterator				oit;
	//double												time;

	//this->clear();
	//for (std::list<GameState*>::const_iterator it = this->_glist.begin();
		 //it != this->_glist.end(); it++)
	//{
		//GameObjectManager::groupsDisplay const	&groups = (*it)->getDisplayObjects();
		//for (lit = groups.begin(); lit != groups.end(); lit++)
		//{
			//if (lit->second->getLayer() >= 0)
			//{
				//time = lit->second->getTimeEffect() * elapsedTime;
				//Group::gameObjectSet const	&objects = lit->second->getObjects();
				//for (oit = objects.begin(); oit != objects.end(); oit++)
				//{
					//static_cast<DrawableObject*>(*oit)->draw(time);
				//}
			//}
		//}
	//}
	//this->flip();
}

void				RendererManager::destroy()
{
}

void				RendererManager::clear()
{
	_window->Clear();
}

void				RendererManager::flip()
{
	_window->Display();
}

//CL_GraphicContext	&RendererManager::getGC()
//{
	//return _gc;
//}

sf::RenderWindow	*RendererManager::getWindow()
{
	if (!_window)
	{
		_window = new sf::RenderWindow(sf::VideoMode(800, 600), "R-Type");
	}
	return _window;
}

//CL_GUIManager		&RendererManager::getGUIManager()
//{
	//return _gui_manager;
//}

//CL_GUIComponent		*RendererManager::getMainWindow()
//{
	//return _window2;
//}

int					RendererManager::getWidth() const
{
	return this->_width;
}

int					RendererManager::getHeight() const
{
	return this->_height;
}
