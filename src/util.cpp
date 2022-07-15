#include "util.hpp"

Util::Util() {}
Util::~Util() {}

/**
 * @brief recebe uma string e tokeniza pelos espacos
 *
 * @param text string que sera tokenizada
 * @param palavras mapa para guardar as palavras com suas quantidades
 */
void Util::tokenizar(std::string text, std::map<std::string, Dado> *palavras, std::string doc) {
	char del = ' ';

	std::stringstream sstream(text);
	std::string word;
	Dado d = Dado(doc);

	std::map<std::string, Dado>::iterator itr;

	while (std::getline(sstream, word, del)) {
		itr = palavras->find(word);
		if (itr != palavras->end()) {
			itr->second.setQuant(itr->second.getQuant() + 1);
		} else
			palavras->insert({ word, d });
	}
}

/**
 * @brief retira os caracteres .,;?!#&%$@()[]{}0123456789 de uma string
 *
 * eh melhor limpar a string antes de passar como parametro, pois tera mais
 * caracteres transitando salvos na memoria
 *
 * @param s string que sera limpa
 */
void Util::cleanLine(std::string &s) {
	std::string chars = ".,;?!#&%$@()[]{}0123456789";

	s.erase(remove_if(s.begin(), s.end(),
		[&chars](const char &c) {
		return chars.find(c) != std::string::npos;
	}), s.end());
}