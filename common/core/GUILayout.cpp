#include "GUILayout.hpp"

GUILayout::GUILayout(int x, int y, int width, int height, int padding, GUILayout *layout, int nbElements)
  : GUIElement(x, y, width, height, layout), _padding(padding), _nbElements(nbElements)
{
  this->_begin = this->_elements.begin();
  this->_focusElement = this->_elements.begin();
  if (this->_isFocused)
    this->focus();
  else
    this->unfocus();
}

GUILayout::GUILayout(int x, int y, int width, int height, int padding, int nbElements)
  : GUIElement(x, y, width, height), _padding(padding), _nbElements(nbElements)
{
  this->_focusElement = this->_elements.begin();
  if (this->_isFocused)
    this->focus();
  else
    this->unfocus();
}

GUILayout::~GUILayout()
{
  for (std::list<GUIElement *>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
      delete *it;
    }
}

void GUILayout::focus()
{
  if (this->_focusElement == this->_elements.end())
    this->nextElement();
  else
    (*this->_focusElement)->focus();
  this->GUIElement::focus();
}

void GUILayout::unfocus()
{
  if (this->_focusElement != this->_elements.end())
    (*this->_focusElement)->unfocus();
  this->GUIElement::unfocus();
}

void GUILayout::insertElementAtBegin(GUIElement &elem)
{
  this->_elements.push_front(&elem);
  this->_begin = this->_elements.begin();
  if (this->_focusElement == this->_elements.end())
    {
      this->_focusElement = this->_elements.begin();
      (*this->_elements.begin())->focus();
    }
}

void GUILayout::insertElementAtEnd(GUIElement &elem)
{
  this->_elements.push_back(&elem);
  this->_begin = this->_elements.begin();
  if (this->_focusElement == this->_elements.end())
    {
      this->_focusElement = this->_elements.begin();
      (*this->_elements.begin())->focus();
    }
}

void GUILayout::prevElement()
{
  if (this->_focusElement == this->_begin)
    {
      if (this->_begin != this->_elements.begin())
	--this->_begin;
      else
	{
	  std::list<GUIElement *>::iterator it = this->_elements.end();
	  for (int i = 0; i < this->_nbElements && it != this->_elements.begin(); ++i)
	    --it;
	  this->_begin = it;
	}
    }

  if (this->_focusElement != this->_elements.end())
    (*this->_focusElement)->unfocus();
  if (this->_focusElement == this->_elements.begin())
    this->_focusElement = --this->_elements.end();
  else
    --this->_focusElement;
  if (this->_focusElement != this->_elements.end())
    {
      if ((*this->_focusElement)->getEnable() == false)
	this->prevElement();
      else
	(*this->_focusElement)->focus();
    }
}

void GUILayout::nextElement()
{
  int nb;

  //for (std::list<GUIElement *>::iterator it = this->_begin; it != this->_elements.end() && nb < this->_nbElements; ++it)
  //++nb;
  //if (nb == this->_nbElements)
  //++this->_begin;
  if (this->_focusElement == this->_elements.end())
    this->_focusElement = this->_elements.begin();
  else if (this->_focusElement == --this->_elements.end())
    {
      (*this->_focusElement)->unfocus();
      this->_focusElement = this->_elements.begin();
    }
  else
    {
    (*this->_focusElement)->unfocus();
      ++this->_focusElement;
    }
  if (this->_focusElement != this->_elements.end())
    {
      if ((*this->_focusElement)->getEnable() == false)
	  this->nextElement();
      else
	(*this->_focusElement)->focus();
    }
}

bool GUILayout::handleGUICommand(InputCommand const &command)
{
  if (this->_focusElement != this->_elements.end())
    return ((*(this->_focusElement))->handleGUICommand(command));
  return (false);
}

void		GUILayout::draw(double elapseTime)
{
  for (std::list<GUIElement *>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
      (*it)->draw(elapseTime);
    }
}

void GUILayout::draw(int x, int y, double elapseTime)
{
  for (std::list<GUIElement *>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
      (*it)->draw(x, y, elapseTime);
    }
}
