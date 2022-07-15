#ifndef DADO_HPP
#define DADO_HPP

#include <iostream>
#include <string>

// using namespace std;

class Dado {
private:
	float quant;
	float IDF;
	std::string doc;
public:
	Dado();
	~Dado();
	Dado(std::string doc);

	void setQuant(float quant);
	float getQuant();

	void setIDF(float IDF);
	float getIDF();

	void setDoc(std::string doc);
	std::string getDoc();
};

#endif