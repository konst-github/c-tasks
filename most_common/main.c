
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "defines.h"
#include "generator.h"
#include "usage.h"
#include "comparator.h"

/** Number of arguments expected.
 NOTE: I don't consider cases when there are no arguments (argv[0] == NULL)
 or when there is some REGEX used, like *.file, what in Unix should probably give us list of files names
 or any other non standard cases

 argv[0] - program name
 argv[1] - path to the file
 */

#define REQUIRED_ARGC_GEN		 	2 // Program name and 'gen' command
#define REQUIRED_ARGC_COMPARE		3 // Program name and 2 file names/paths
#define CMP_RESULT_EQUAL 0

#define RUN_RESULT_INVALID -1
#define RUN_RESULT_SUCCESS 0
#define RUN_RESULT_GEN_SUCCESS 1


FILE * open_file(const char file_path[]);
LONG file_size(FILE * file);
void compare_files(FILE * file1, FILE * file2);


char * cmd_gen = "gen";


int main(int argc, const char *argv[])
{
	// 0. Output received command line arguments

	printf("\nCommand-line arguments:\n");
	for(int n = 0; n < argc; n++)
	{
		printf("%d. '%s'\n", (n + 1), argv[n]);
	}
	printf("\n");


	// 1. Check if we've received a correct number of arguments

	if (argc == REQUIRED_ARGC_GEN)
	{
		// 2. Check if 'gen' command execution requested
		if(strcmp(argv[1], cmd_gen) == CMP_RESULT_EQUAL)
		{
			printf("Received 'gen' command ->\n\n");
			printf("Starting test files generation\n\n");

			generate_files();

			return RUN_RESULT_GEN_SUCCESS;
		}
		else
		{
			print_usage();
			return RUN_RESULT_INVALID;
		}
	}
	else if(argc == REQUIRED_ARGC_COMPARE)
	{
		// 3. Try to open file for reading

		FILE * file1 = open_file(argv[1]);
		if(file1 == NULL)
		{
			return RUN_RESULT_INVALID;
		}

		FILE * file2 = open_file(argv[2]);
		if(file2 == NULL)
		{
			return RUN_RESULT_INVALID;
		}

		// 4. Start reading file and converting string
		compare_files(file1, file2);

		return RUN_RESULT_SUCCESS;
	}
	else {
		print_usage();
		return RUN_RESULT_INVALID;
	}
}


FILE * open_file(const char file_path[])
{
	FILE * file;

	if ((file = fopen(file_path, "r")) == NULL)
	{
		perror("Error opening file. Please check if path is correct or file exists.\n");
		print_usage();
		return NULL;
	}

	printf("File %s opened successfully\n", file_path);

	return file;
}


LONG file_size(FILE * file)
{
	fseek(file, 0 , SEEK_END);
	LONG size = ftell(file);
	fseek(file, 0 , SEEK_SET); // needed for the next read from the beginning of file
	printf("File size is %lu bytes\n\n", size);
	return size;
}


void compare_files(FILE * file1, FILE * file2)
{
	LONG size1 = file_size(file1);
	LONG size2 = file_size(file2);

	time_t time_start, time_end;

	time(&time_start);
	printf("COMPARING FILES START: size1 = %lu, size2 = %lu, time = %lu", size1, size2, time_start);



	time(&time_end);
	printf("COMPARING FILES END: time = %lu, elapsed = %f", time_end, difftime(time_end - time_start));
}
