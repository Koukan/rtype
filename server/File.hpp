#pragma once

#include "Net.hpp"

class File
{
  public:
    File();
    ~File();
	bool		load(std::string const &path);

  private:
	std::list<Net::DataBlock*>	_list;
	std::string					_md5;
};
