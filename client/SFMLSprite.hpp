#pragma once

#include <SFML/Graphics.hpp>
#include "Sprite.hpp"

class SFMLSprite : public Sprite, public sf::Sprite
{
	public:
		struct		Rect
		{
			uint32_t		x;
			uint32_t		y;
			uint32_t		width;
			uint32_t		height;
		};
		SFMLSprite(double x = 0, double y = 0);
		SFMLSprite(std::string const &name, ResourceManager &resources,
				   double x = 0, double y = 0);
		virtual ~SFMLSprite();
		void			update(double elapsedTime);
		void			setFrameRate(double rate);
		void			setRepeat(bool repeat);
		void			setPingpong(bool pingpong);
		void			setUp(bool up);
		void			setTranslate(int x, int y);
		void			setGrid(uint32_t top, uint32_t left, uint32_t width,
								uint32_t height, uint32_t nbx, uint32_t nby,
								uint32_t spacex, uint32_t spacey);

		virtual void	draw();
		virtual void	draw(double elapsedTime);
		virtual void	draw(int x, int y);
		virtual void	draw(int x, int y, double elapsedTime);

	private:
		sf::RenderWindow			*_window;
		double						_frameRate;
		double						_lastTime;
		double						_currentTime;
		bool						_repeat;
		bool						_pingpong;
		bool						_up;
		uint32_t					_currentFrame;
		int							_tx;
		int							_ty;
		std::vector<sf::IntRect>	_rect;
};
