#include "utils.hpp"
#include <fstream>
namespace utils
{
	std::string readFile(std::string const & file_path)
	{
		std::ifstream stream{ file_path, std::ios::ate };
		if (!stream.is_open())
		{
			return "file" + file_path + "not found";
		}
		size_t size = stream.tellg();
		std::string file;
		file.resize(size);
		stream.seekg(0);
		stream.read(file.data(), size);
		return file;
	}
}