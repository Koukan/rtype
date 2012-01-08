#include "ButtonSprite.hpp"
#include "GameStateManager.hpp"

ButtonSprite::ButtonSprite(std::string const &buttonSprite,
			   std::string const &buttonSelectedSprite,
			   std::string const &buttonClickedSprite,
			   int width, int height)
  : _width(width), _height(height), _state(ButtonSprite::DEFAULT)
{
  GameState *gameState = &(GameStateManager::get().getCurrentState());

  this->_defaultSprite = gameState->getSprite(buttonSprite);
  this->_selectedSprite = gameState->getSprite(buttonSelectedSprite);
  this->_clickedSprite = gameState->getSprite(buttonClickedSprite);

  gameState->getGUI().registerButtonSprite(*this);
}

ButtonSprite::~ButtonSprite()
{
  delete this->_defaultSprite;
  delete this->_selectedSprite;
  delete this->_clickedSprite;
}

void ButtonSprite::updateState(enum ButtonSprite::eState state)
{
  this->_state = state;
}

void ButtonSprite::draw(int x, int y, double elapseTime)
{
  if (_state == DEFAULT && this->_defaultSprite)
    this->_defaultSprite->draw(x, y, elapseTime);
  else if (_state == SELECTED && this->_selectedSprite)
    this->_selectedSprite->draw(x, y, elapseTime);
  else if (_state == CLICKED && this->_clickedSprite)
    this->_clickedSprite->draw(x, y, elapseTime);
}

int ButtonSprite::getWidth()
{
  return this->_width;
}

int ButtonSprite::getHeight()
{
  return this->_height;
}
