#include "utils.hpp"
#include <fstream>
#include <vector>
namespace utils
{
	std::vector<char> readFile(std::string const & file_path)
	{
		std::ifstream stream{ file_path, std::ios::ate |std::ios::binary };
		if (!stream.is_open())
		{
			//return { "file" + file_path + "not found" };
			return std::vector<char>();
		}
		size_t size = stream.tellg();
		std::vector<char> file;
		file.resize(size);
		stream.seekg(0);
		stream.read(file.data(), size);
		return file;
	}
}