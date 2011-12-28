#include <iostream>
#include "ResourceManager.hpp"

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
	std::cout << "Document" << std::endl;
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

void			ResourceManager::loadComment(TiXmlNode *parent)
{
}

void			ResourceManager::loadUnknown(TiXmlNode *parent)
{
}

void			ResourceManager::loadText(TiXmlNode *parent)
{
}

void			ResourceManager::loadDeclaration(TiXmlNode *parent)
{
}

void			ResourceManager::loadSprite(TiXmlNode *parent)
{
	std::list<Arg>		arg;

	this->getAttribute(static_cast<TiXmlElement*>(parent), arg);
}

void			ResourceManager::getAttribute(TiXmlElement *element,
											  std::list<Arg> &list)
{
	Arg			arg;

	for (TiXmlAttribute	*attrib = element->FirstAttribute(); attrib != 0;
		 attrib = attrib->Next())
	{
		arg.name = attrib->Name();
		arg.data = attrib->Value();
		list.push_back(arg);
	}
}
