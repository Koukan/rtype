#pragma once

#include <map>
#include <list>
#include "BulletResourceManager.hpp"
#include "tinyxml.h"
#include "Sprite.hpp"
#include "SpriteProvider.hpp"

class ResourceManager : public BulletResourceManager
{
  public:
	ResourceManager();
	virtual ~ResourceManager();
	void			load(std::string const &path);
	void			loadSpriteProvider(SpriteProvider &provider);
	Sprite			*getSprite(std::string const &name) const;

  private:
	template <typename T>
	struct			Method
	{
		T			name;
		void		(ResourceManager::*func)(TiXmlNode*);
	};

	template <typename T>
	struct			Method_2
	{
		std::string	name;
		void		(ResourceManager::*func)(TiXmlElement*, T);
	};

	void			load(TiXmlNode *parent);
	template <typename T>
	void			loadElement(TiXmlNode *parent, T data,
								Method_2<T> const *tab, size_t sizeTab);
	void			loadDocument(TiXmlNode *parent);
	void			loadElement(TiXmlNode *parent);
	void			loadComment(TiXmlNode *parent);
	void			loadUnknown(TiXmlNode *parent);
	void			loadText(TiXmlNode *parent);
	void			loadDeclaration(TiXmlNode *parent);
	void			loadSprite(TiXmlNode *parent);
	void			get2Int(std::string const &data, std::string const &sep,
							int &a, int &b);

	// sprite parsing
	void			imageSprite(TiXmlElement *parent, Sprite *sprite);
	void			scaleSprite(TiXmlElement *parent, Sprite *sprite);
	void			animationSprite(TiXmlElement *parent, Sprite *sprite);
	void			translateSprite(TiXmlElement *parent, Sprite *sprite);
	void			gridSprite(TiXmlElement *parent, Sprite *sprite);

	SpriteProvider	*_provider;
	TiXmlDocument	_document;
};

#include "ResourceManager.ipp"
