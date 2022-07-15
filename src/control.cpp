#include "control.hpp"

Control::Control() {}
Control::~Control() {}

void Control::initRelGeral() {
	std::string key;

	for (int i = 1; i <= MAX; i++) {
		key.assign("doc").append(std::to_string(i));
		this->rel_geral.insert({ key, 0 });
	}
}

void Control::processar() {
	carregaDocuments();
	calculaIDF();
	initRelGeral();
	calculaTF_IF();
}

void Control::carregaDocuments() {
	std::string file;

	Read r = Read();

	r.readFile("input", &this->input, "");
	r.readFile("stop", &this->vec);

	removeStopWords(this->input);

	// le os 6 documentos e guarda em uma lista
	for (int i = 0; i < MAX; i++) {
		file.assign("doc").append(std::to_string(i + 1));
		r.readFile(file, &this->document, file);

		removeStopWords(this->document);

		this->lista.push_back(document);
		this->document.clear();
	}
}

void Control::removeStopWords(std::map<std::string, Dado> &words) {
	for (std::string stop : this->vec) {
		this->itr = words.find(stop);
		if (this->itr != words.end()) words.erase(itr);
	}
}

void Control::calculaIDF() {
	for (this->itr = this->input.begin(); this->itr != this->input.end(); ++this->itr) {
		this->itr->second.setIDF(0);

		for (this->itrList = this->lista.begin(); this->itrList != this->lista.end(); ++this->itrList) {
			this->itrFound = this->itrList->find(this->itr->first);
			if (this->itrFound != this->itrList->end()) this->itr->second.setIDF(this->itr->second.getIDF() + 1);
		}
		if (this->itr->second.getIDF() != 0) this->itr->second.setIDF(std::log10((MAX / itr->second.getIDF())));
	}
}

void Control::calculaTF_IF() {
	Dado d = Dado();

	for (this->itr = this->input.begin(); this->itr != this->input.end(); ++this->itr) {
		this->dados.clear();

		if (this->itr->second.getIDF() != 0) {
			for (this->itrList = this->lista.begin(); this->itrList != this->lista.end(); ++this->itrList) {
				this->itrFound = this->itrList->find(this->itr->first);

				if (this->itrFound != this->itrList->end()) {
					d.setDoc(this->itrFound->second.getDoc());
					d.setIDF(this->itr->second.getIDF() * (this->itrFound->second.getQuant() / this->itrList->size()));
					this->dados.push_back(d);

					this->itr_relgeral = this->rel_geral.find(d.getDoc());
					if (this->itr_relgeral != this->rel_geral.end()) this->itr_relgeral->second += d.getIDF();
				}
			}
		}
		this->rel_palavra.insert({ this->itr->first, this->dados });
	}
}

void Control::printAllWords() {
	std::cout << "Relevancia de cada palavra de entrada" << std::endl << std::endl;

	for (this->itr_rel = this->rel_palavra.begin();
		this->itr_rel != this->rel_palavra.end(); ++this->itr_rel) {
		std::cout << "[ " << this->itr_rel->first << " ] -> ";

		if (this->itr_rel->second.size() != 0) {
			for (Dado d : this->itr_rel->second)
				std::cout << d.getDoc() << " " << d.getIDF() << " | ";
			std::cout << std::endl;
		} else
			std::cout << " Nao possui relevancia" << std::endl;
		std::cout << std::endl;
	}
}

void Control::printGeral() {
	std::cout << "Relevancia geral dos documentos" << std::endl << std::endl;

	for (this->itr_relgeral = this->rel_geral.begin(); this->itr_relgeral != this->rel_geral.end(); this->itr_relgeral++)
		std::cout << this->itr_relgeral->first << " " << this->itr_relgeral->second << std::endl;
}