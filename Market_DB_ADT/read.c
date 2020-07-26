/*
 * read.c
 *
 *  Created on: Jun 13, 2020
 *      Author: SuperMoudy
 */

#include <stdio.h>
#include <ctype.h>
#include "read.h"

void read_word(char *word, int word_len)
{
	char ch;
	int count = 0;

	// Ignore white-space characters
	while(isspace(ch = getchar()));

	// Check the end of the string
	while(ch != '\n' && count < word_len)
	{
		*word++ = ch; // Read input char
		count++; // Increase string length
		ch = getchar(); // Read a new character
	}
	*word = '\0'; // Null terminated string

	// Empty the input buffer from extra input chars
	if(ch != '\n')
		while(getchar() != '\n');
}
