/*
 * main.c
 *
 *  Created on: Jun 13, 2020
 *      Author: SuperMoudy
 */

#include <stdio.h>
#include <string.h>
#include "read.h"
#include "market.h"

int main(void)
{
	// Variables
	char pass[21] = "myinventory", input_pass[21], command;
	int pass_count = 1;
	Market_DB inventory = create();

	// Password Entering
	for(; pass_count < 4; pass_count++)
	{
		printf("Enter password: ");
		read_word(input_pass, 20);

		if(!strcmp(input_pass, pass)) // input_pass == pass
			break;
		else
			printf("Wrong password\n\n");
	}

	if(pass_count == 4) // Exceeded 3 wrong times
		return 0; // Exit the program

	// User-interface
	for(;;)
	{
		printf("Enter command: ");
		scanf(" %c", &command);

		if(command == INSERT) // i
		{
			add_item(inventory);
		}
		else if(command == DELETE) // d
		{
			remove_item(inventory);
		}
		else if(command == BILL) // b
		{
			scan_list(inventory);
		}
		else if(command == MODIFY) // m
		{
			modify_item(inventory);
		}
		else if(command == PRINT) // p
		{
			print_list(inventory);
		}
		else if(command == QUIT) // q
		{
			break; // Break the loop to end the program
		}
		else // Otherwise is a wrong command
		{
			printf("Wrong command\n");
		}
		printf("\n"); // Line Break for a better view
	}

	return 0;
}
