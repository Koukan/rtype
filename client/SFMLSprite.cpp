#include "SFMLSprite.hpp"
#include "RendererManager.hpp"

SFMLSprite::SFMLSprite(double x, double y)
	: _window(RendererManager::get().getWindow()), _frameRate(-1),
	  _lastTime(0), _currentTime(0), _repeat(false), _pingpong(false),
	  _up(true), _currentFrame(0), _tx(0), _ty(0)
{
	this->setX(x);
	this->setY(y);
}

SFMLSprite::~SFMLSprite()
{
}

void		SFMLSprite::update(double elapsedTime)
{
	if (this->_frameRate == -1)
		return ;
	uint32_t	size = this->_rect.size();
	if (size < 2 || (!this->_pingpong && !this->_repeat &&
					 this->_currentFrame >= (size - 1)))
		return ;
	this->_currentTime += elapsedTime;
	double		tmp = this->_currentTime - this->_lastTime;
	double		time = this->_frameRate / size;
	uint32_t	nbr;
	int			nb = this->_currentFrame;
	if (tmp > time)
	{
		nbr = static_cast<int>(tmp) / static_cast<int>(time);
		this->_lastTime += time * nbr;
		if (this->_pingpong)
		{
			while (nbr)
			{
				nb += (this->_up) ? 1 : -1;
				if (nb == size)
					this->_up = false;
				else if (nb == 0)
					this->_up = true;
				nbr--;
			}
		}
		else if (this->_repeat)
			nb = (nb + nbr) % (size + 1);
		else
		{
			nb = nb + nbr;
			if (nb > size)
				nb = size;
		}
		this->_currentFrame = nb;
		this->SetSubRect(this->_rect[this->_currentFrame]);
	}
}

void		SFMLSprite::setFrameRate(double rate)
{
	this->_frameRate = rate;
}

void		SFMLSprite::setRepeat(bool repeat)
{
	this->_repeat = repeat;
}

void		SFMLSprite::setPingpong(bool pingpong)
{
	this->_pingpong = pingpong;
}

void		SFMLSprite::setUp(bool up)
{
	this->_up = up;
}

void		SFMLSprite::setTranslate(int x, int y)
{
	this->_tx = x;
	this->_ty = y;
}

void		SFMLSprite::setGrid(uint32_t left, uint32_t top, uint32_t width,
								uint32_t height, uint32_t nbx, uint32_t nby,
								uint32_t spacex, uint32_t spacey)
{
	uint32_t		nb;
	uint32_t		x;

	for (; nby != 0; nby--)
	{
		x = left;
		for (nb = nbx; nb != 0; nb--)
		{
			this->_rect.push_back(sf::IntRect(x, top, width, height));
			x += spacex + width;
		}
		top += spacey + height;
	}
}

void		SFMLSprite::draw()
{
	this->SetPosition(this->_x + this->_tx, this->_y + this->_ty);
	this->_window->Draw(*this);
}

void		SFMLSprite::draw(double elapsedTime)
{
	this->update(elapsedTime);
	this->SetPosition(this->_x + this->_tx, this->_y + this->_ty);
	this->_window->Draw(*this);
}

void		SFMLSprite::draw(int x, int y)
{
	this->SetPosition(x + this->_tx, y + this->_ty);
	this->_window->Draw(*this);
}

void		SFMLSprite::draw(int x, int y, double elapsedTime)
{
	this->update(elapsedTime);
	this->SetPosition(x + this->_tx, y + this->_ty);
	this->_window->Draw(*this);
}
