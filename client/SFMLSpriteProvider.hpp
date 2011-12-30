#pragma once

#include <SFML/Graphics.hpp>
#include "SpriteProvider.hpp"
#include "SFMLSprite.hpp"

class SFMLSpriteProvider : public SpriteProvider
{
  public:
    SFMLSpriteProvider();
    virtual ~SFMLSpriteProvider();
	virtual Sprite	*addSprite(std::string const &name);
	virtual Sprite	*getSprite(std::string const &name) const;
	virtual void	addImage(std::string const &path, Sprite &sprite);

  private:
	typedef	std::map<std::string, SFMLSprite*>	SpritesMap;
	typedef	std::map<std::string, sf::Texture*>	ImagesMap;

	SpritesMap		_sprites;
	ImagesMap		_images;
};
