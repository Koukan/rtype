#include "CreateMap.hpp"

static std::map<Keyboard::Key, char>	GUITextBoxCharMap = CreateMap<Keyboard::Key, char>
  (Keyboard::A, 'a')
  (Keyboard::B, 'b')
  (Keyboard::C, 'c')
  (Keyboard::D, 'd')
  (Keyboard::E, 'e')
  (Keyboard::F, 'f')
  (Keyboard::G, 'g')
  (Keyboard::H, 'h')
  (Keyboard::I, 'i')
  (Keyboard::J, 'j')
  (Keyboard::K, 'k')
  (Keyboard::L, 'l')
  (Keyboard::M, 'm')
  (Keyboard::N, 'n')
  (Keyboard::O, 'o')
  (Keyboard::P, 'p')
  (Keyboard::Q, 'q')
  (Keyboard::R, 'r')
  (Keyboard::S, 's')
  (Keyboard::T, 't')
  (Keyboard::U, 'u')
  (Keyboard::V, 'v')
  (Keyboard::W, 'w')
  (Keyboard::X, 'x')
  (Keyboard::Y, 'y')
  (Keyboard::Z, 'z')
  (Keyboard::Num0, '0')
  (Keyboard::Num1, '1')
  (Keyboard::Num2, '2')
  (Keyboard::Num3, '3')
  (Keyboard::Num4, '4')
  (Keyboard::Num5, '5')
  (Keyboard::Num6, '6')
  (Keyboard::Num7, '7')
  (Keyboard::Num8, '8')
  (Keyboard::Num9, '9')
  (Keyboard::Period, '.')
  (Keyboard::Dash, '-')
  (Keyboard::Numpad0, '0')
  (Keyboard::Numpad1, '1')
  (Keyboard::Numpad2, '2')
  (Keyboard::Numpad3, '3')
  (Keyboard::Numpad4, '4')
  (Keyboard::Numpad5, '5')
  (Keyboard::Numpad6, '6')
  (Keyboard::Numpad7, '7')
  (Keyboard::Numpad8, '8')
  (Keyboard::Numpad9, '9');