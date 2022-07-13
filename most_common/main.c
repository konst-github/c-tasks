
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

	/*
		Conditions:
		- 	files consist only of ASCII characters
		- 	a word is delimited by any non-alphanumeric character
		- 	both files are warmed up and are in the operating system buffer cache
		- 	test files span 2GB each
		- 	optimize for speed.

		Problems and constraints:
		- 	main problem is in processing of 2 huge files, so we need to process them in chunks;
		- 	processing of both files one by one will increase time of processing drastically;
		-	we also can't keep all unique words in memory (especially considering worst scenario when all words at all are unique);
		- 	also we should have extra processing to split words - considering 'any non-alphanumeric character' as any characted in ASCII table
			different from a...z + A...Z + 0...9, plus lowercase each word (since f.e. 'word' and 'Word' are same words for statistics);
		-	we can't store the most common word during processing of chunks from files and drop remained from memory (to the file f.e.), because
			during processing of further chunks any word from dropped ones can become the actual most common one
			(so we'll need to process dropped words from files again - what increases overall processing time,
			plus this makes no sense to use minHeap f.e. suggested in Geeks for Geeks f.e. for such a task).

		Solutions:
		a) processing files:
		- 	Process both files simultaneously - each file in its own thread.
		- 	Process each file using fgetc (no sense to use fread, as it calls fgetc) (removing extra loop for processing chunk).
		- 	If character is between a...z + 0...9 - concate it to the pending word, if between A...Z - lowercase (use table map from 'lowercase' task) - concat.
		- 	To avoid (re)allocation as much as possible - array for pending word should be of size f.e. 45 chars
			(longest word in English dictionary - Pneumonoultramicroscopicsilicovolcanoconiosis, not counting some ~190K words :-))
			and if word appears to be longer - reallocate array to store more characters.
		- 	When non-character is met - store word and continue.
		b) processing words:
		- 	store each word in an array, for each first word's letter or number allocate separate array, so array for words starting from 'a' , array for 'b's etc.
			since numerics are also included - array for each number or word starting from number (f.e. if address will appear, like 123Lane street).
		- 	or use f.e. Trie or B-Tree, but again separately for each letter and number. Calling it storage for now.
			(not sure yet which storage will be better for now - find it experimantally, because those data structures are fast, but require a huge amount of space).
		- 	search if word already exists in storage - YES - increase counter, NO - add word with counter = 1.
		- 	control total size of storage, drop it to the file every time it's size close or equals to maximum allowed size of memory, clean storage.
			(so basically use some kind of a database stored on SSD).
		- 	after every drop of storage we'll have chunks of data with already calculated number of words appearance.
		- 	when both files are processed - we'll need to read each storage for each letter, process it again to merge duplicated words
	*/

	time(&time_end);
	printf("COMPARING FILES END: time = %lu, elapsed = %f", time_end, difftime(time_end - time_start));
}
