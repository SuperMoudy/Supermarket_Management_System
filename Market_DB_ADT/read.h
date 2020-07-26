/*
 * read.h
 *
 *  Created on: Jun 13, 2020
 *      Author: SuperMoudy
 */

#ifndef READ_H_
#define READ_H_

// Constants correspond to the input commands
enum command_list
{
	INSERT = (int)'i', DELETE = (int)'d',
	BILL = (int)'b', MODIFY = (int)'m',
	PRINT = (int)'p', QUIT = (int)'q'
};

// Enhanced function for reading strings
void read_word(char *word, int word_len);

#endif /* READ_H_ */
