#pragma once

#include <string>
#include "SpriteProvider.hpp"
#include "Singleton.hpp"
#include "ResourceManager.hpp"
#include "File.hpp"

class ServerResourceManager : public Singleton<ServerResourceManager>, public SpriteProvider, public ResourceManager
{
  public:
    ServerResourceManager();
    virtual ~ServerResourceManager();
	virtual Sprite	*addSprite(std::string const &);
	virtual Sprite	*getSprite(std::string const &);
	virtual void	addImage(std::string const &path, Sprite &);
	void			loadResource(std::string const &path);

  private:
	std::map<std::string, File*>	_res;
};
