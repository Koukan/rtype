#include "ButtonSprite.hpp"

ButtonSprite::ButtonSprite(std::string const &buttonSprite,
			   std::string const &buttonSelectedSprite,
			   std::string const &buttonClickedSprite)
{
  GameState *gameState = &(GameStateManager::get().getCurrentState());

  this->_defaultButton = gameState->getSprite(buttonSprite);
  this->_selectedButton = gameState->getSprite(buttonSelectedSprite);
  this->_clickedButton = gameState->getSprite(buttonClickedSprite);
}

ButtonSprite::~ButtonSprite()
{
  delete this->_defaultButton;
  delete this->_selectedButton;
  delete this->_clickedButton;  
}

ButtonSprite::draw(int x, int y, double elapseTime)
{
  if (_state == DEFAULT)
    this->_defaultSprite->draw(x, y, elapseTime);
  else if (_state == SELECTED)
    this->_selectedSprite->draw(x, y, elapseTime);
  else if (_state == CLICKED)
    this->_clickedSprite->draw(x, y, elapseTime);
}
