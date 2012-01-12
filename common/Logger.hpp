#pragma once
#include <iostream>
#include "PacketType.hpp"
#include "Clock.hpp"

class Logger
{
private:
  class Log
  {
  public:
    Log(std::map<PacketType::ContactState::State, std::string> const &states,
	std::map<PacketType::Call::Call, std::string> const &calls);

	Log(Log const &log) :
		_states(log._states), _calls(log._calls), _end(true)
	{
	}

    ~Log()
    {
#if defined (_WIN32)
	if (_end)
#endif
      std::cout << std::endl;
    }

    template<typename T>
    Log& operator<<(T const &t)
    {
      std::cout << t;
      return (*this);
    }
    Log &operator<<(PacketType::ContactState::State state);
    Log &operator<<(PacketType::Call::Call state);

  private:
    std::map<PacketType::ContactState::State, std::string> const &_states;
    std::map<PacketType::Call::Call, std::string> const &_calls;
	bool _end;
  };

public:
  Logger();

  template<typename T>
  Log operator<<(T const &t)
  {
    Log log(_states, _calls);

    log << "[" << Clock::getTimeInStr() << "] ";
    log << t;

    return (log);
  }

  static Logger logger;

private:
  std::map<PacketType::ContactState::State, std::string> _states;
  std::map<PacketType::Call::Call, std::string> _calls;
};
