#include "ServerResourceManager.hpp"

ServerResourceManager::ServerResourceManager() : _id(1)
{
}

ServerResourceManager::~ServerResourceManager()
{
}

Sprite		*ServerResourceManager::addSprite(
				std::string const &name)
{
	if (this->_ids.find(name) == this->_ids.end())
		this->_ids[name] = _id++;
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

uint32_t	ServerResourceManager::getId(std::string const &name) const
{
	std::map<std::string, uint32_t>::const_iterator it = _ids.find(name);

	if (it != this->_ids.end())
		return it->second;
	return 0;
}
