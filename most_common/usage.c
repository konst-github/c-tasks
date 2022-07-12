
#include <stdio.h>

#include "usage.h"

void print_usage()
{
	printf("\n===== MOST COMMON WORD APPLICATION USAGE =====\n"
		   "\n"
		   "Commands:\n"
		   "\tgen\t\tGenerate test files. Needs 4Gb of free disk space.\n"
		   "\n"
		   "\n"
		   "Arguments:\n"
		   "\t[input_file_1] [input_file_2]\n\n"
		   "\tExamples:\n"
		   "\t\tmost_common file1.txt file2.txt\n"
		   "\t\tmost_common ./file1.txt ./file2.txt\n"
		   "\t\tmost_common /Users/username/test/lowercase/file1.txt /Users/username/test/lowercase/file2.txt\n"
		   "\n=======================================\n"
		   "\n"
		   );
}
