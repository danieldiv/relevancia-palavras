#include "read.hpp"

Read::Read() {}
Read::~Read() {}

/**
 * @brief realiza a leitura de um arquivo e salva em um map
 *
 * @param file nome do arquivo a ser aberto
 * @param palavras map para guardar as palavras com suas quantidades
 *
 * se tiver problemas de fim de linha, utilize
 * if (!myfile.eof())  line.erase(line.end() - 1);
 */
void Read::readFile(std::string file, std::map<std::string, Dado> *palavras, std::string doc) {
	file.insert(0, "files/").append(".txt");

	std::ifstream myfile(file);
	std::string line;

	Util u = Util();

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			u.cleanLine(line);
			u.tokenizar(line, palavras, doc);
		}
		myfile.close();
	} else std::cout << "nao foi possivel abrir o arquivo" << std::endl;
}

/**
 * @brief realiza a leitura de um arquivo e salva em um vetor
 *
 * @param file nome do arquivo a ser aberto
 * @param vec vetor para guardar as informacoes
 */
void Read::readFile(std::string file, std::vector<std::string> *vec) {
	file.insert(0, "files/").append(".txt");

	std::ifstream myfile(file);
	std::string line;

	if (myfile.is_open())
		while (getline(myfile, line)) vec->push_back(line);
	else std::cout << "nao foi possivel abrir o arquivo" << std::endl;
}