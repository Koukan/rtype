#ifndef		_GAME_
#define 	_GAME_

#define PREF_FILE ".preferences"

#include <fstream>
#include <string>
#include <vector>
#include "Singleton.hpp"
#include "GameStateManager.hpp"
#include "ModuleManager.hpp"

class Game : public Singleton<Game>, public ModuleManager
{
public:
  Game();
  virtual ~Game();
  void		init();
  void		quit();

  void		readPreferencesFile();
  void		savePreferencesFile(std::string const &name = "", std::string const &ip = "", std::string const &port = "");
  std::string const &getName() const;
  std::string const &getIP() const;
  std::string const &getPort() const;

private:
  bool		_quit;
  std::fstream _preferencesFile;
  std::vector<std::string>	_preferences; // 0 = IP, 1 = port
};

#endif		/* _GAME_ */
