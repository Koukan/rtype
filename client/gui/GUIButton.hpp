#pragma once

#include "GUIElement.hpp"
#include <string>

template <typename T>
class GUIButton : public GUIElement
{
public:
  GUIButton(T &instance, void (*T::func)(), std::string const &name, ButtonSprite &sprite, int x = 0, int y = 0, int width = 0, int height = 0)
    : GUIElement(x, y, width, height), _instance(&instance), _sprite(&sprite)
  {
  }

  ~GUIButton();

  void handleFunction()
  {
    (this->instance->(*this->_func))();
  }

  virtual void	draw(double elapseTime)
  {
    this->_sprite->draw();
  }
  

private:
  T *_instance;
  void (*T::_func)();
  ButtonSprite *_sprite;
};
