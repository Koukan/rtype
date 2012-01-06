#include <fstream>
#include "File.hpp"

File::File()
{
}

File::~File()
{
}

bool		File::load(std::string const &path)
{
	std::ifstream	file(path.c_str());
	char			*buffer;
	size_t			size = 1300;

	if (file)
	{
		while (!file.eof())
		{
			buffer = new char[size];
			file.read(buffer, size);
			if (file.eof())
				size = file.gcount();
			this->_list.push_back(new Net::DataBlock(buffer, size));
		}
	}
}
