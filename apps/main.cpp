#include <time.h>

#include "control.hpp"

int main() {
	clock_t time = clock();

	Control c = Control();
	c.processar();
	c.printAllWords();
	c.printGeral();

	std::cout << std::endl << "tempo: " << (((clock() - time) / (double)CLOCKS_PER_SEC)) << " segundos" << std::endl;

	return EXIT_SUCCESS;
}