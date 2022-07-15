#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

#include <vector>
#include <list>
#include <map>

#include <time.h>

#include "dado.hpp"

#define MAX 6

void readFile(std::string file, std::map<std::string, Dado> *palavras, std::string doc);
void readFile(std::string file, std::vector<std::string> *vec);
void tokenizar(std::string text, std::map<std::string, Dado> *palavras, std::string doc);
void cleanLine(std::string &str);

int main() {
	clock_t time = clock();
	std::string file;

	std::map<std::string, Dado> input;
	std::map<std::string, Dado> document;
	std::map<std::string, Dado>::iterator itr;
	std::map<std::string, Dado>::iterator itrFound;

	std::vector<std::string> vec;
	std::list<std::map<std::string, Dado>> lista;
	std::list<std::map<std::string, Dado>>::iterator itrList;

	readFile("input", &input, "");
	readFile("stop", &vec);

	// retira as stops words da entrada
	for (std::string stop : vec) {
		itr = input.find(stop);
		if (itr != input.end()) input.erase(itr);
	}

	// le os 6 documentos e guarda em uma lista
	for (int i = 0; i < MAX; i++) {
		file.assign("doc").append(std::to_string(i + 1));
		readFile(file, &document, file);

		for (std::string stop : vec) {
			itr = document.find(stop);
			if (itr != document.end()) document.erase(itr);
		}
		lista.push_back(document);
		document.clear();
	}

	// calcula o IDF
	for (itr = input.begin(); itr != input.end(); ++itr) {
		itr->second.setIDF(0);

		for (itrList = lista.begin(); itrList != lista.end(); ++itrList) {
			itrFound = itrList->find(itr->first);
			if (itrFound != itrList->end()) itr->second.setIDF(itr->second.getIDF() + 1);
		}
		if (itr->second.getIDF() != 0) itr->second.setIDF(std::log10((MAX / itr->second.getIDF())));
	}

	std::map<std::string, std::vector<Dado>> rel_palavra; // relevancia por palavra
	std::map<std::string, std::vector<Dado>>::iterator itr_rel;
	std::vector<Dado> dados;
	Dado d = Dado();

	std::map<std::string, float> rel_geral; // relevancia geral
	std::map<std::string, float>::iterator itr_relgeral; // relevancia geral

	rel_geral.insert({ "doc1", 0 });
	rel_geral.insert({ "doc2", 0 });
	rel_geral.insert({ "doc3", 0 });
	rel_geral.insert({ "doc4", 0 });
	rel_geral.insert({ "doc5", 0 });
	rel_geral.insert({ "doc6", 0 });

	// realiza TF * IDF
	for (itr = input.begin(); itr != input.end(); ++itr) {
		dados.clear();

		if (itr->second.getIDF() != 0) {
			for (itrList = lista.begin(); itrList != lista.end(); ++itrList) {
				itrFound = itrList->find(itr->first);

				if (itrFound != itrList->end()) {
					d.setDoc(itrFound->second.getDoc());
					d.setIDF(itr->second.getIDF() * (itrFound->second.getQuant() / itrList->size()));
					dados.push_back(d);

					itr_relgeral = rel_geral.find(d.getDoc());
					if (itr_relgeral != rel_geral.end()) itr_relgeral->second += d.getIDF();
				}
			}
		}
		rel_palavra.insert({ itr->first, dados });
	}

	for (itr_relgeral = rel_geral.begin(); itr_relgeral != rel_geral.end(); itr_relgeral++)
		std::cout << itr_relgeral->first << " " << itr_relgeral->second << std::endl;

	// imprime os dados de relevancia de cada palavra
	// for (itr_rel = rel_palavra.begin();
	// 	itr_rel != rel_palavra.end(); ++itr_rel) {
	// 	std::cout << "[ " << itr_rel->first << " ] -> ";

	// 	if (itr_rel->second.size() != 0) {
	// 		for (Dado d : itr_rel->second)
	// 			std::cout << d.getDoc() << " " << d.getIDF() << " | ";
	// 		std::cout << std::endl;
	// 	} else
	// 		std::cout << " Nao possui relevancia" << std::endl;
	// 	std::cout << std::endl;
	// }

	std::cout << std::endl << "tempo: " << (((clock() - time) / (double)CLOCKS_PER_SEC)) << std::endl;

	return EXIT_SUCCESS;
}

/**
 * @brief realiza a leitura de um arquivo e salva em um std::map
 *
 * @param file nome do arquivo a ser aberto
 * @param palavras std::map para guardar as palavras com suas quantidades
 *
 * se tiver problemas de fim de linha, utilize
 * if (!myfile.eof())  line.erase(line.end() - 1);
 */
void readFile(std::string file, std::map<std::string, Dado> *palavras, std::string doc) {
	file.insert(0, "files/").append(".txt");

	std::ifstream myfile(file);
	std::string line;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			cleanLine(line);
			tokenizar(line, palavras, doc);
		}
		myfile.close();
	} else std::cout << "nao foi possivel abrir o arquivo" << std::endl;
}

/**
 * @brief realiza a leitura de um arquivo e salva em um veto
 *
 * @param file nome do arquivo a ser aberto
 * @param vec vetor para guardar as informacoes
 */
void readFile(std::string file, std::vector<std::string> *vec) {
	file.insert(0, "files/").append(".txt");

	std::ifstream myfile(file);
	std::string line;

	if (myfile.is_open())
		while (getline(myfile, line)) vec->push_back(line);
	else std::cout << "nao foi possivel abrir o arquivo" << std::endl;
}

/**
 * @brief recebe uma std::string e tokeniza pelos espacos
 *
 * @param text std::string que sera tokenizada
 * @param palavras std::mapa para guardar as palavras com suas quantidades
 */
void tokenizar(std::string text, std::map<std::string, Dado> *palavras, std::string doc) {
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
void cleanLine(std::string &s) {
	std::string chars = ".,;?!#&%$@()[]{}0123456789";

	s.erase(remove_if(s.begin(), s.end(),
		[&chars](const char &c) {
		return chars.find(c) != std::string::npos;
	}), s.end());
}