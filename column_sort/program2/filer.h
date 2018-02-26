#pragma once
#include "utility.h"
#define FILER_H

//header file FILER.H for class filer
//a class object can create a file of a specified
//number of random integers in a specified range

class Filer
{
public:
	void makefile(int n, int range, string file_name);
	//precondition: n, range, and file_name have 
	//been set; 
	//postcondition: n random integers in the range 0-range,
	//inclusive, have been written to a file named file_name,
	//one per line;

private:
	int next_number(int range);
	//precondition:  range has been set to a nonnegative value
	//postcondition:  returns a random integer in the range
	//0-range, inclusive

};
