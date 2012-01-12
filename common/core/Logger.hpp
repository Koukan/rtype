#pragma once
#include <iostream>
#include "Clock.hpp"

class Logger
{
private:
  class Log
  {
  public:
    Log(Log const &log) :
		_end(true)
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

  private:
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
};