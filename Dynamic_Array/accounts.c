/*
 * accounts.c
 *
 *  Created on: Jun 11, 2020
 *      Author: SuperMoudy
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // C99
#include "accounts.h"

void insert_account(Item *account, int *size, int *max_size)
{
	char name[NAME_LEN + 1];

	// Make sure we don't run out of array memory
	if(*size == *max_size)
	{
		*max_size *= 2; // Double the old size

		Item *temp_account = realloc(account, *max_size * sizeof(Item));

		// Reallocation failed hence memory can't take more action
		if(temp_account == NULL)
		{
			printf("Memory is full!");
			exit(EXIT_FAILURE);
		}
		else
		{
			// Memory is good to go
			account = temp_account;
		}

	}

	// Enter item name
	printf("Enter item name: ");
	gets(name);


	// Check if name exists
	// If exists: print item already exists
	for(int i = 0; i < *size; i++)
	{
		if(!strcmp(name, account[i].name))
		{
			printf("This item already exists\n");
			return;
		}
	}

	
	// If not: continue
	strcpy(account[*size].name, name);

	// Enter item id
	printf("Enter item id: ");
	scanf("%d", &account[*size].id);

	// Check if id exists
	while (id_exists(account, *size, account[*size].id))
	{
		printf("Id exists, enter another: ");
		scanf("%d", &account[*size].id);
	}

	// Enter item amount
	printf("Enter item amount: ");
	scanf("%d", &account[*size].amount);

	// Enter item price
	printf("Enter item price: ");
	scanf("%d", &account[*size].price);

	(*size)++;

	// Indicate the process is sucessfull
	printf("insert operation successful.\n");
}

void pay_receipt(Item *account, int size)
{
	// New receipt initialization code
	int receipt_max_size = 10, receipt_current_size = 0; // Starting sizes
	int id, amount;
	int *items_index = malloc(receipt_max_size * sizeof(int));
	int *items_amount = malloc(receipt_max_size * sizeof(int));

	// Enter various ids
	printf("Enter item id: ");
	scanf("%d", &id);

	// Non-positive id is the only stopping condition
	while(id > 0)
	{
		// Is receipt full?
		if(receipt_current_size == receipt_max_size)
		{
			receipt_max_size *= 2;

			int *temp_items_index = 
				realloc(temp_items_index, receipt_max_size * sizeof(int));
			int *temp_items_amount = 
				realloc(temp_items_amount, receipt_max_size * sizeof(int));

			// If reallocation failed, the memory can't take any more
			if(temp_items_index == NULL || temp_items_amount == NULL)
			{
				printf("Memory is full\n");
				exit(EXIT_FAILURE);
			}
			else // If reallocation succeeded, we are good to go
			{
				items_index = temp_items_index;
				items_amount = temp_items_amount;
			}

		}

		if(!id_exists(account, size, id))
		{
			printf("Id doesn't exist, enter another one: ");
			scanf("%d", &id);
			continue;
		}

		// Find the item index with the given id
		for(int i = 0; i < size; i++)
		{
			if(account[i].id == id)
			{
				items_index[receipt_current_size] = i;
				break;
			}
		}

		// For each id enter the amount
		printf("Enter amount to buy: ");
		scanf("%d", &amount);
		items_amount[receipt_current_size] = amount;

		// Update the original account
		account[items_index[receipt_current_size++]].amount -= amount;


		printf("Enter item id: ");
		scanf("%d", &id);
	}

	// Print a table of items bought containing:
	// amount of each item, item name, total price of item
	printf("Amount   Item                   Price\n");
	for(int i = 0; i < receipt_current_size; i++)
	{
		printf("%4d     %-20s %6d\n", items_amount[i], account[items_index[i]].name
				, account[items_index[i]].price * items_amount[i]);
	}

	// Indicate the process is sucessfull
	printf("pay operation successful.\n");
}

void modify_account(Item *account, int size)
{
	char name[NAME_LEN + 1], item_member;
	int index, id, amount, price;
	bool item_exists = false;

	// Enter item name
	printf("Enter item name: ");
	gets(name);

	// Search if name exists
	for(int i = 0; i < size; i++)
	{
		if(!strcmp(account[i].name, name))
		{
			item_exists = true;
			index = i;
			break;
		}
	}

	if(!item_exists)
	{
		printf("Item does not exist\n");
		return;
	}

	printf("Enter which data to update\n");
	printf("i = id, a = amount, p = price: ");
	scanf(" %c", &item_member);

	switch(item_member)
	{
	case 'i':
		printf("Enter new id: ");
		scanf("%d", &id);
		while (id_exists(account, size, id))
		{
			printf("Id exists, enter another: ");
			scanf("%d", &account[size].id);
		}
		account[index].id = id;
		break;

	case 'a':
		printf("Enter new amount: ");
		scanf("%d", &amount);
		account[index].amount = amount;
		break;

	case 'p':
		printf("Enter new price: ");
		scanf("%d", &price);
		account[index].price = price;
		break;

	default:
		printf("Invalid input\n");
		return;
	}


	// Indicate the process is sucessfull
	printf("modify operation successful.\n");
}

void print_all(Item *account, int size)
{
	// Print the data of all items as a table
	printf("Item name              Item ID   Amount   Price\n");
	for(int i = 0; i < size; i++)
	{
		printf("%-20s   %5d    %6d  %6d\n", account[i].name, account[i].id,
				account[i].amount, account[i].price);
	}

	// Indicate the process is sucessfull
	printf("print operation successful.\n");
}

void delete_account(Item *account, int *size)
{
	char name[NAME_LEN + 1];
	int index;
	bool item_exists = false;

	// Make sure that the account table is not empty
	if(*size == 0)
	{
		printf("There is no account to be deleted\n");
		return;
	}


	// Enter name
	printf("Enter item name: ");
	gets(name);

	// Search item and delete it if it exists
	for(int i = 0; i < *size; i++)
	{
		if(!strcmp(name, account[i].name))
		{
			item_exists = true;
			index = i;
		}
	}


	// In case of wrong item name
	if(!item_exists)
	{
		printf("Item does not exist\n");
		return;
	}

	// Update the account table
	for(int i = index + 1; i < *size; i++)
	{
		strcpy(account[i - 1].name, account[i].name);
		account[i - 1].id = account[i].id;
		account[i - 1].amount = account[i].amount;
		account[i - 1].price = account[i].price;
	}
	(*size)--;

	// Indicate the process is sucessfull
	printf("delete operation successful.\n");
}

int id_exists(Item *account, int size, int id)
{
	for(int i = 0; i < size; i++)
	{
		if(account[i].id == id)
			return id;
	}

	return 0;
}

