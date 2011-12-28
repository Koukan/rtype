#pragma once

#include <map>
#include <list>
#include <SFML/Graphics.hpp>
#include "BulletResourceManager.hpp"
#include "tinyxml.h"

class Sprite;
class SFMLSprite;

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
	void			load(std::string const &path);
	Sprite			*getSprite(std::string const &name) const;

  private:
	typedef std::map<std::string, SFMLSprite*>	SpritesMap;
	typedef std::map<std::string, sf::Texture*>	ImagesMap;

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
	SFMLSprite		*addSprite(std::string const &name);
	sf::Texture		*addImage(std::string const &path);
	void			get2Int(std::string const &data, std::string const &sep,
							int &a, int &b);

	// sprite parsing
	void			imageSprite(TiXmlElement *parent, SFMLSprite *sprite);
	void			scaleSprite(TiXmlElement *parent, SFMLSprite *sprite);
	void			animationSprite(TiXmlElement *parent, SFMLSprite *sprite);
	void			translateSprite(TiXmlElement *parent, SFMLSprite *sprite);
	void			gridSprite(TiXmlElement *parent, SFMLSprite *sprite);

	TiXmlDocument	_document;
	SpritesMap		_sprites;
	ImagesMap		_images;
};

#include "ResourceManager.ipp"
