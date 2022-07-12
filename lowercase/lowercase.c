
#include <stdio.h>
#include <time.h>

#include "defines.h"
#include "lowercase.h"

#define CHUNK_SIZE (2*1024*1024)


void strlwr(char * string);
void strlwr_tbl(char * string);


void lowercase(FILE * file, LONG size)
{
	time_t time_start, time_end;
	time(&time_start);
	printf("STARTING LOWERCASE CONVERSION, time: %lu\n", time_start);

	size_t num_bytes_read = 0;

	char bytes[CHUNK_SIZE];

	while( num_bytes_read < size )
	{
		num_bytes_read += fread(bytes, sizeof(char), CHUNK_SIZE, file);
//		printf("\nBYTES READ = %lu\n", num_bytes_read);

//		strlwr(bytes);
		strlwr_tbl(bytes);
	}

	// Parse and output
	time(&time_end);
	printf("\nFINISHED LOWERCASE CONVERSION, time: %lu, elapsed: %f\n\n", time_end, difftime(time_end, time_start));
}


// Obvious approach
void strlwr(char * string) {
	char *p = string;
	for ( ; *p; ++p)
	{
		// Lowercase letters in ASCII table have decimal values from 97 to 122, what means bits 6 and 7 are set.
		// Uppercase letters have decimal values from 65 to 90, so by setting bits 6 and 7 to 1 we lowercase those letters
		// 0x60 = 0b01100000
		// or we can just add 32 to lowercase character

		*p = ((*p >= 'A') && (*p <= 'Z')) ? (*p | 0x60) : *p;
	}

	printf("%s", string);

	// Measurements for the generated file on MBPR late 2015
	// ~97 seconds in total with printf output
	// ~17 seconds in total without printf output
}


// Extra attempt to make it faster - table map approach
// https://stackoverflow.com/questions/63005177/is-there-a-faster-way-to-lowercase-a-string-in-c

const char ascii_table[256] =
{
	['a'] = 'a', ['A'] = 'a',
	['b'] = 'b', ['B'] = 'b',
	['c'] = 'c', ['C'] = 'c',
	['d'] = 'd', ['D'] = 'd',
	['e'] = 'e', ['E'] = 'e',
	['f'] = 'f', ['F'] = 'f',
	['g'] = 'g', ['G'] = 'g',
	['h'] = 'h', ['H'] = 'h',
	['i'] = 'i', ['I'] = 'i',
	['j'] = 'j', ['J'] = 'j',
	['k'] = 'k', ['K'] = 'k',
	['l'] = 'l', ['L'] = 'l',
	['m'] = 'm', ['M'] = 'm',
	['n'] = 'n', ['N'] = 'n',
	['o'] = 'o', ['O'] = 'o',
	['p'] = 'p', ['P'] = 'p',
	['q'] = 'q', ['Q'] = 'q',
	['r'] = 'r', ['R'] = 'r',
	['s'] = 's', ['S'] = 's',
	['t'] = 't', ['T'] = 't',
	['u'] = 'u', ['U'] = 'u',
	['v'] = 'v', ['V'] = 'v',
	['w'] = 'w', ['W'] = 'w',
	['x'] = 'x', ['X'] = 'x',
	['y'] = 'y', ['Y'] = 'y',
	['z'] = 'z', ['Z'] = 'z',
};


void strlwr_tbl(char * string)
{
	char c;
	unsigned char *ustr = string; // unsigned - as used as array index

	while(*ustr)
	{
		c = ascii_table[*ustr];
		if(c) *ustr = c;
		ustr++;
	}

	printf("%s", string);

	// Measurements for the generated file on MBPR late 2015
	// ~94 seconds in total with printf output
	// ~6-7 seconds in total without printf output
}
