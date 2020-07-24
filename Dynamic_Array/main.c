/*
 * main.c
 *
 *  Created on: Jun 11, 2020
 *      Author: SuperMoudy
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // C99
#include "accounts.h"

// Macros
#define PW_LEN 20
#define MAX_PW_TRIALS 3
#define PASSWORD ("admin")

// Starting dynamic array initializations
int max_size = 5; // Starting max size
int current_size = 0;
Item *account = NULL;

int main(void)
{
	char password[PW_LEN + 1], op_code;
	bool correct_pw = false;

	account = malloc(max_size * sizeof(Item));

	// Login operation
	for(int i = 0; i < MAX_PW_TRIALS; i++)
	{
		printf("Enter password: ");
		//scanf("%s", password);
        gets(password);

		// Comparing input password with the set one
		if(!strcmp(password, PASSWORD))
		{
			correct_pw = true; // Setting correction flag
			break;
		}
		else
		{
			printf("wrong password\n\n");
		}
	}

	while(correct_pw) // If flag is set, we can continue running
	{
		printf("\n");
		printf("Enter operation: "); // Taking input op code
		scanf(" %c", &op_code);
		while(getchar() != '\n');

		switch(op_code)
		{
		case 'i': insert_account(account, &current_size, &max_size); break;
		case 'b': pay_receipt(account, current_size); break;
		case 'm': modify_account(account, current_size); break;
		case 'p': print_all(account, current_size); break;
		case 'd': delete_account(account, &current_size); break;
		case 'q': return 0;
		default: printf("Invalid operation.\n"); // Wrong op code
		}
	}

	return 0;
}
