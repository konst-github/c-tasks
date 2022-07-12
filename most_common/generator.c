
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "generator.h"


#define KiB							1024u
#define MiB							(KiB * KiB)
#define GiB							(KiB * MiB)

#define MAX_FILE_LENGTH 			(GiB * 2)

#define LENGTH_ALPHABET 			26
#define MIN_WORD_LENGTH				5
#define MAX_WORD_LENGTH				200
#define WORD_LENGTH_SPREAD			(MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1)
	
#define DIFF_UPPER_LOWER_ASCII 		('a' - 'A')


void strgen(int size, char str[]);


const char alphabet[LENGTH_ALPHABET] =
{
	'a', 'b', 'c',
	'd', 'e', 'f',
	'g', 'h', 'i',
	'j', 'k', 'l',
	'm', 'n', 'o',
	'p', 'q', 'r',
	's', 't', 'u',
	'v', 'w', 'x',
	'y', 'z'
};


int generate_files()
{

//	unsigned long int bytesWritten = 0u;
//
//	char * path = "words.txt";
//	FILE * file = fopen(path, "w");
//
//	if(!file)
//	{
//		printf("Can't open/create file for writing");
//		return -1;
//	}
//
//	time_t time_start, time_end;
//	time(&time_start);
//	printf("generateTestFile START: %lu\n", time_start);
//
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
//		printf("generateTestFile %lu bytes written\n", bytesWritten);
//	}
//
//	time(&time_end);
//	printf("generateTestFile END: %lu , ELAPSED: %f\n", time_end, difftime(time_end, time_start));
//
//	if(fclose(file))
//	{
//		perror(path);
//		return -1;
//	}

	return 0;
}


void strgen(int size, char str[])
{
	for(int n = 0; n < size-1; n++)
	{
		int index = random() % LENGTH_ALPHABET;
		char letter = alphabet[index];

		bool is_upper = (random() % 2) > 0;
		if(is_upper)
		{
			letter -= DIFF_UPPER_LOWER_ASCII;
		}
		str[n] = letter;
	}

	str[size - 1] = '\n';
}
