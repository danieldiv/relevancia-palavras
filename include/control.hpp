#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <cmath>
#include <list>

#include "read.hpp"

class Control {
private:
	std::map<std::string, float> rel_geral;
	std::map<std::string, Dado> input;
	std::map<std::string, Dado> document;
	std::map<std::string, std::vector<Dado>> rel_palavra; // relevancia por palavra

	std::vector<std::string> vec;
	std::vector<Dado> dados;
	std::list<std::map<std::string, Dado>> lista;

	std::map<std::string, Dado>::iterator itr;
	std::map<std::string, Dado>::iterator itrFound;
	std::map<std::string, std::vector<Dado>>::iterator itr_rel;
	std::map<std::string, float>::iterator itr_relgeral;
	std::list<std::map<std::string, Dado>>::iterator itrList;

	void initRelGeral();
	void calculaIDF();
	void calculaTF_IF();
	void carregaDocuments();
	void removeStopWords(std::map<std::string, Dado> &words);
public:
	Control();
	~Control();

	void processar();
	void printAllWords();
	void printGeral();
};
#endif