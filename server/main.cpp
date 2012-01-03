#include "Server.hpp"
#if defined (WIN32)
#include <direct.h>
#define chdir _chdir
#endif

int		main(int ac, char **av)
{
  std::string		path = av[0];

  chdir(path.substr(0, path.rfind('/')).c_str());
  try
  {
	if (ac > 1)
		Server::get().init(av[1]);
	else
		Server::get().init();
    return 0;
  }
  catch (...)
  {
	std::cerr << "Unhandled Exception" << std::endl;
    return 1;
  }
  return 0;
}
