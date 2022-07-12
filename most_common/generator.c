
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "defines.h"
#include "generator.h"


#define KiB							1024u
#define MiB							(KiB * KiB)
#define GiB							(KiB * MiB)

#define MAX_FILE_LENGTH 			(GiB * 2)


void strgen(int size, char str[]);
int generate_file(char * path);


int generate_files()
{
	generate_file("words_1.txt");
	generate_file("words_2.txt");
	return 0;
}

int generate_file(char * path)
{
	LONG bytesWritten = 0u;

	FILE * file = fopen(path, "w");

	if(!file)
	{
		printf("Can't open/create file for writing");
		return -1;
	}

	time_t time_start, time_end;
	time(&time_start);
	printf("generate_file %s START: %lu\n", path, time_start);

//	while(bytesWritten < MAX_FILE_LENGTH)
//	{
//		int length_to_gen = MIN_WORD_LENGTH + (random() % WORD_LENGTH_SPREAD);
//
//		if(bytesWritten + length_to_gen > MAX_FILE_LENGTH)
//		{
//			break;
//		}
//
//		char str[length_to_gen];
//
//		strgen(length_to_gen, str);
//
//		bytesWritten += fwrite(str, sizeof(char), length_to_gen, file);
//
//		printf("generate_file: %lu bytes written\n", bytesWritten);
//	}

	time(&time_end);
	printf("generate_file %s END: %lu , ELAPSED: %f\n", path, time_end, difftime(time_end, time_start));

	if(fclose(file))
	{
		perror(path);
		return -1;
	}

	return 0;
}
