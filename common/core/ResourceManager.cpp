#include <iostream>
#include "ResourceManager.hpp"
#include "SFMLSprite.hpp"
#include "Converter.hpp"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void			ResourceManager::load(std::string const &path)
{
	if (!this->_document.LoadFile(path.c_str()))
		throw std::exception();
	load(&this->_document);
}

Sprite			*ResourceManager::getSprite(std::string const &name) const
{
	SpritesMap::const_iterator	it = this->_sprites.find(name);

	if (it != this->_sprites.end())
		return new SFMLSprite(*it->second);
	return 0;
}

void			ResourceManager::load(TiXmlNode *parent)
{
	static Method<TiXmlNode::NodeType> const	methods[] = {
			{TiXmlNode::DOCUMENT, &ResourceManager::loadDocument},
			{TiXmlNode::ELEMENT, &ResourceManager::loadElement},
			{TiXmlNode::COMMENT, &ResourceManager::loadComment},
			{TiXmlNode::UNKNOWN, &ResourceManager::loadUnknown},
			{TiXmlNode::TEXT, &ResourceManager::loadText},
			{TiXmlNode::DECLARATION, &ResourceManager::loadDeclaration}
	};
	size_t					i;
	TiXmlNode::NodeType		type;

	if (!parent)
		return ;
	for (TiXmlNode *child = parent->FirstChild(); child != 0;
		 child = child->NextSibling())
	{
		type = static_cast<TiXmlNode::NodeType>(child->Type());
		for (i = 0; i != (sizeof(methods) / sizeof(*methods)); i++)
		{
			if (type == methods[i].name)
			{
				(this->*methods[i].func)(child);
				break ;
			}
		}
	}
}

void			ResourceManager::loadDocument(TiXmlNode *parent)
{
	this->load(parent);
}

void			ResourceManager::loadElement(TiXmlNode *parent)
{
	static Method<std::string> const	methods[] = {
			{"resources", &ResourceManager::load},
			{"sprite", &ResourceManager::loadSprite}
	};
	std::string		name;
	size_t			i;

	for (TiXmlNode *child = parent->FirstChild(); child != 0;
		 child = child->NextSibling())
	{
		name = child->Value();
		for (i = 0; i != (sizeof(methods) / sizeof(*methods)); i++)
		{
			if (name == methods[i].name)
			{
				(this->*methods[i].func)(child);
				break ;
			}
		}
	}
}

void			ResourceManager::loadComment(TiXmlNode *)
{
}

void			ResourceManager::loadUnknown(TiXmlNode *)
{
}

void			ResourceManager::loadText(TiXmlNode *)
{
}

void			ResourceManager::loadDeclaration(TiXmlNode *)
{
}

void			ResourceManager::loadSprite(TiXmlNode *parent)
{
	static Method_2<SFMLSprite*> const	methods[] = {
			{"image", &ResourceManager::imageSprite},
			{"animation", &ResourceManager::animationSprite},
			{"scale", &ResourceManager::scaleSprite},
			{"translation", &ResourceManager::translateSprite}
	};
	SFMLSprite			*sprite = 0;
	std::string			name;

	for (TiXmlAttribute	*attrib = static_cast<TiXmlElement*>(parent)->FirstAttribute();
		 attrib != 0; attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "name")
			sprite = this->addSprite(attrib->Value());
	}
	if (sprite)
		this->loadElement(static_cast<TiXmlElement*>(parent), sprite,
						  methods, sizeof(methods) / sizeof(*methods));
}

SFMLSprite		*ResourceManager::addSprite(std::string const &name)
{
	SFMLSprite				*sprite = 0;
	SpritesMap::iterator	it = this->_sprites.find(name);

	if (it == this->_sprites.end())
	{
		sprite = new SFMLSprite;
		this->_sprites[name] = sprite;
	}
	else
		sprite = it->second;
	return sprite;
}

sf::Texture		*ResourceManager::addImage(std::string const &path)
{
	sf::Texture			*texture;
	ImagesMap::iterator	it = this->_images.find(path);

	if (it == this->_images.end())
	{
		texture = new sf::Texture;
		if (!texture->LoadFromFile(path))
			std::cerr << "Image at " << path << " was not found." << std::endl;
		this->_images[path] = texture;
	}
	else
		texture = it->second;
	return texture;
}

void		ResourceManager::get2Int(std::string const &data,
									 std::string const &sep,
									 int &a, int &b)
{
	size_t	pos = data.find(sep);

	a = Converter::toInt<int>(data);
	if (pos == std::string::npos)
		b = 0;
	else
		b = Converter::toInt<int>(data.substr(pos));
}

// sprite parsing

void	ResourceManager::imageSprite(TiXmlElement *parent, SFMLSprite *sprite)
{
	static Method_2<SFMLSprite*> const	methods[] = {
			{"grid", &ResourceManager::gridSprite}
	};
	std::string name;

	for (TiXmlAttribute *attrib = parent->FirstAttribute(); attrib != 0;
		 attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "file")
			sprite->SetTexture(*this->addImage(attrib->Value()));
	}
	this->loadElement(parent, sprite, methods,
					  sizeof(methods) / sizeof(*methods));
}

void	ResourceManager::scaleSprite(TiXmlElement *parent, SFMLSprite *sprite)
{
	std::string	name;
	float		x = 1;
	float		y = 1;

	for (TiXmlAttribute	*attrib = parent->FirstAttribute(); attrib != 0;
		 attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "x")
			x = Converter::toInt<float>(attrib->Value());
		else if (name == "y")
			y = Converter::toInt<float>(attrib->Value());
	}
	sprite->SetScale(x, y);
}

void	ResourceManager::animationSprite(TiXmlElement *parent, SFMLSprite *sprite)
{
	std::string	name;

	for (TiXmlAttribute	*attrib = parent->FirstAttribute(); attrib != 0;
		 attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "speed")
			sprite->setFrameRate(Converter::toInt<double>(attrib->Value()));
		else if (name == "loop")
			sprite->setRepeat((attrib->Value() == "yes") ? true : false);
		else if (name == "pingpong")
			sprite->setPingpong((attrib->Value() == "yes") ? true : false);
	}
}

void	ResourceManager::translateSprite(TiXmlElement *parent, SFMLSprite *sprite)
{
	int			x = 0;
	int			y = 0;
	std::string	name;

	for (TiXmlAttribute	*attrib = parent->FirstAttribute(); attrib != 0;
		 attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "x")
			x = Converter::toInt<int>(attrib->Value());
		else if (name == "y")
			y = Converter::toInt<int>(attrib->Value());
	}
	sprite->setTranslate(x, y);
}

void	ResourceManager::gridSprite(TiXmlElement *parent, SFMLSprite *sprite)
{
	int			x = 0, y = 0;
	int			width = 0, height = 0;
	int			nbx = 0, nby = 0;
	int			spacex = 0, spacey = 0;
	std::string name;

	for (TiXmlAttribute *attrib = parent->FirstAttribute(); attrib != 0;
		 attrib = attrib->Next())
	{
		name = attrib->Name();
		if (name == "pos")
			this->get2Int(attrib->Value(), ",", x, y);
		else if (name == "size")
			this->get2Int(attrib->Value(), ",", width, height);
		else if (name == "array")
			this->get2Int(attrib->Value(), ",", nbx, nby);
		else if (name == "spacing")
			this->get2Int(attrib->Value(), ",", spacex, spacey);
	}
	sprite->setGrid(x, y, width, height, nbx, nby, spacex, spacey);
}
// end sprite parsing
