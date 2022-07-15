#ifndef READ_HPP
#define READ_HPP

#include <fstream>
#include <vector>

#include "util.hpp"

class Read {
private:
public:
	Read();
	~Read();
	void readFile(std::string file, std::map<std::string, Dado> *palavras, std::string doc);
	void readFile(std::string file, std::vector<std::string> *vec);
};

#endif