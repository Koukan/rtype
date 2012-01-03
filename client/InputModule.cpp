#include <SFML/Graphics.hpp>
#include <cstring>
#include "RendererManager.hpp"
#include "GameStateManager.hpp"
#include "CommandDispatcher.hpp"
#include "Input.hpp"
#include "InputModule.hpp"

InputModule::InputModule() : Module("InputModule", 20)
{
}

InputModule::~InputModule()
{
}

void		InputModule::init()
{
}

void		InputModule::update(double)
{
 sf::Event  ev;
		
 sf::RenderWindow *ptr = RendererManager::get().getWindow();
 #if (SFML_VERSION_MAJOR == 2)
 while (ptr->PollEvent(ev))
 #else
 while (ptr->GetEvent(ev))
 #endif
 {
	InputCommand *tmp = new InputCommand();
	tmp->Type = static_cast<InputCommand::EventType>(ev.Type);
	::memcpy(&tmp->Size, &ev.Size, 12);
	CommandDispatcher::get().pushCommand(*tmp);
 }
}

void        InputModule::destroy()
{
}

