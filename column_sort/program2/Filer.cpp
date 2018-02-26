#include "utility.h"
#include"filer.h"

	void Filer::makefile(int n, int range, string file_name) {
		ofstream infile;
		infile.open(file_name);
		srand(int(time(NULL)));
		for (int i = 0; i < n; i++) {
			infile << Filer::next_number(range)<< endl;
		}

	}

	int Filer::next_number(int range) {
		int r1 = rand() % (range + 1);
		return r1;
	}