#include "ServerResourceManager.hpp"

ServerResourceManager::ServerResourceManager()
{
}

ServerResourceManager::~ServerResourceManager()
{
}

Sprite		*ServerResourceManager::addSprite(
				std::string const &)
{
	return new Sprite;
}

Sprite		*ServerResourceManager::getSprite(
				std::string const &)
{
	return 0;
}

void		ServerResourceManager::addImage(
				std::string const &path, Sprite &)
{
	if (this->_resources.find(path) == this->_resources.end())
	{
		File	*file = new File;
		if (file->load(path))
			this->_resources[path] = file;
		else
			delete file;
	}
}
