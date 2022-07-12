
#include <stdio.h>

#include "usage.h"

void printUsage() {
	printf("\n===== LOWERCASE APPLICATION USAGE =====\n"
		   "\n"
		   "Commands:\n"
		   "\tgen\t\tGenerate test file. Needs 2Gb of free disk space.\n"
		   "\n"
		   "\n"
		   "Arguments:\n"
		   "\t[input_file]\n\n"
		   "\tExamples:\n"
		   "\t\tlowercase file.txt\n"
		   "\t\tlowercase ./file.txt\n"
		   "\t\tlowercase /Users/username/test/lowercase/file.txt\n"
		   "\n=======================================\n"
		   "\n"
		   );
}
