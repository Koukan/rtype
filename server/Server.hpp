#pragma once

#include "ModuleManager.hpp"
#include "ThreadPool.hpp"
#include "Singleton.hpp"
#include "GameManager.hpp"

class Server : public ModuleManager, public Singleton<Server>,
			   public GameManager, public ThreadPool
{
  public:
    Server();
    virtual ~Server();
	int				init(std::string const &port = "25557");
};
