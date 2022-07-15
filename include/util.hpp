#ifndef UTIL_HPP
#define UTIL_HPP

#include <algorithm>
#include <sstream>
#include <string>
#include <map>

#include "dado.hpp"

#define MAX 6

class Util {
private:
public:
	Util();
	~Util();
	void tokenizar(std::string text, std::map<std::string, Dado> *palavras, std::string doc);
	void cleanLine(std::string &str);
};

#endif