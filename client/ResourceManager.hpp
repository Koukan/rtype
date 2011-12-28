#pragma once

#include <list>
#include "BulletResourceManager.hpp"
#include "tinyxml.h"

//#if defined(_WIN32)
//typedef		std::shared_ptr<sf::Texture>		ImagePtr;
//#else
//typedef		std::tr1::shared_ptr<sf::Texture>	ImagePtr;
//#endif

class ResourceManager : public BulletResourceManager
{
  public:
	ResourceManager();
	virtual ~ResourceManager();
	void				load(std::string const &path);

  private:
	template <typename T>
	struct				Method
	{
		T				name;
		void			(ResourceManager::*func)(TiXmlNode*);
	};
	struct				Arg
	{
		std::string		name;
		std::string		data;
	};

	void				load(TiXmlNode *parent);
	void				loadDocument(TiXmlNode *parent);
	void				loadElement(TiXmlNode *parent);
	void				loadComment(TiXmlNode *parent);
	void				loadUnknown(TiXmlNode *parent);
	void				loadText(TiXmlNode *parent);
	void				loadDeclaration(TiXmlNode *parent);
	void				loadSprite(TiXmlNode *parent);
	void				getAttribute(TiXmlElement *parent, std::list<Arg> &list);
	TiXmlDocument		_document;
};
