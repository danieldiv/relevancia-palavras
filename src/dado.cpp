#include "dado.hpp"

Dado::Dado() {}
Dado::~Dado() {}

Dado::Dado(std::string doc) {
	setQuant(1);
	setDoc(doc);
}

void Dado::setQuant(float quant) { this->quant = quant; }
void Dado::setIDF(float IDF) { this->IDF = IDF; }
void Dado::setDoc(std::string doc) { this->doc = doc; }

float Dado::getQuant() { return this->quant; }
float Dado::getIDF() { return this->IDF; }
std::string Dado::getDoc() { return this->doc; }