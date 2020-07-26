/*
 * market.c
 *
 *  Created on: Jun 13, 2020
 *      Author: SuperMoudy
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "market.h"

// Constants correspond to the item properties
enum item_type
{
	ID = (int)'i', AMOUNT = (int)'a', PRICE = (int)'p'
};

// Item structure
struct item
{
	char name[21];
	pval id;
	pval amount;
	pval price;
	struct item *next;
};

// Database of items data structure
struct market_database
{
	struct item *first;
	struct item *last;
};

// Hidden function for possible errors
static void terminate(const char *message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

// Hidden utility to be used when needed
static char *get_name(Market_DB inv, pval id)
{
	struct item *temp = inv->first;

	// Look for the item with the given id
	for(; temp != NULL; temp = temp->next)
		if(temp->id == id)
			return temp->name;

	return NULL; // item is not found
}

static bool find_id(Market_DB inv, pval id)
{
	struct item *temp = inv->first;

	// Look for the item with the given id
	for(; temp != NULL; temp = temp->next)
		if(temp->id == id)
			return true;

	return false; // item is not found

}

Market_DB create(void)
{
	Market_DB inv = malloc(sizeof(struct market_database));

	if(inv == NULL)
		terminate("Error in create: memory is full.");

	// Initialize the database
	inv->first = NULL;
	inv->last = NULL;

	return inv;
}

bool is_empty(Market_DB inv)
{
	return inv->first == NULL;
}

void add_item(Market_DB inv)
{
	struct item *new_item = malloc(sizeof(struct item));
	struct item *temp = inv->first;
    int id;

	if(new_item == NULL)
		terminate("Error in add: memory is full.");

	printf("Enter item name: ");
	read_word(new_item->name, 20);

	// Find the name
	for(; temp != NULL; temp = temp->next)
	{
		if(!strcmp(temp->name, new_item->name))
			break;
	}

	// If name is not found, then it's a new one
	if(temp == NULL)
	{
		// If database is originally empty
		if(is_empty(inv))
		{
			// Insert the item as the first item
			inv->first = new_item;
			inv->last = inv->first;
            new_item->id = 0; // To avoid problems in id verification
		}
		else // Database was not empty before
		{
			// Insert the item as the last item
			inv->last->next = new_item;
			inv->last = inv->last->next;
		}
        new_item->next = NULL;

		// Ask for additional data
		printf("Enter item id: ");
		scanf("%u", &id);

		for(; find_id(inv, id);)
		{
			printf("Id taken, enter another id: ");
			scanf("%u", &id);
		}
        
        new_item->id = id;

		printf("Enter item amount: ");
		scanf("%u", &new_item->amount);

		printf("Enter item price: ");
		scanf("%u", &new_item->price);
	}
	else
	{
		// Item is already there so we delete
		printf("Item already in the inventory\n");
		free(new_item);
	}


}


void remove_item(Market_DB inv)
{
	char name[21];
	struct item *temp = inv->first, *prev = NULL;

	// We can't delete an item for an empty database
	if(is_empty(inv))
	{
		printf("Nothing to be deleted (empty)\n");
		return;
	}

	// If database is not empty
	printf("Enter item name: ");
	read_word(name, 20);

	// Find if name in database
	for(; temp != NULL; prev = temp, temp = temp->next)
	{
		if(!strcmp(temp->name, name))
			break;
	}

	if(temp == NULL)
	{
		printf("Item is not found\n");
		return;
	}

	if(temp == inv->first)
	{
		// If the deleted item is the first
		inv->first = inv->first->next;
	}
	else if(temp == inv->last)
	{
		// If the deleted item is the last
		prev->next = NULL;
		inv->last = prev;
	}
	else
	{
		// If the deleted item neither first nor last
		prev->next = temp->next;
	}

	// Delete item
	free(temp);
}

void print_list(Market_DB inv)
{
	struct item *temp;

	printf("\nInventory:\n");
	printf("Name                        ID   Amount   Price\n");

	for(temp = inv->first; temp != NULL; temp = temp->next)
		printf("%-20s      %4u    %4u   %5u\n", temp->name, temp->id,
				temp->amount, temp->price);

}

void modify_item(Market_DB inv)
{
	char name[21], item;
	struct item *temp;

	// We can't modify an item in an empty database
	if(is_empty(inv))
	{
		printf("Inventory is empty\n");
		return;
	}
	temp = inv->first;

	printf("Enter item name: ");
	read_word(name, 20);

	// Find the item to modify
	for(; temp != NULL; temp = temp->next)
	{
		if(!strcmp(temp->name, name))
			break;
	}

	// Item entered is not in the database
	if(temp == NULL)
	{
		printf("Item is not found\n");
		return;
	}

	// Item is in database and we want to choose
	// what to modify
	printf("Enter data to be updated: ");
	scanf(" %c", &item);

	if(item == ID)
	{
		printf("Enter new ID: ");
		scanf("%u", &temp->id);

		for(; find_id(inv, temp->id);)
		{
			printf("Id taken, enter another id: ");
			scanf("%u", &temp->id);
		}

	}
	else if(item == AMOUNT)
	{
		printf("Enter new amount: ");
		scanf("%u", &temp->amount);
	}
	else if(item == PRICE)
	{
		printf("Enter new price: ");
		scanf("%u", &temp->price);
	}
	else // We entered a wrong item type
	{
		printf("Wrong data\n");
		return;
	}
}


void scan_list(Market_DB inv)
{
	// Dynamic array of ids, amounts, price
	int size = 0, total_size = 5;
	pval id;
	struct item *temp_item;
	pval *temp_arr;

	// Receipt to be printed
	pval *id_list = malloc(total_size * sizeof(pval));
	pval *amount_list = malloc(total_size * sizeof(pval));
	pval *price_list = malloc(total_size * sizeof(pval));

	while(1)
	{
		printf("Enter id: ");
		scanf("%u", &id);

		// If receipt size is not enough to insert a new item
		if(size == total_size)
		{
			total_size *= 2;
			temp_arr = realloc(id_list, total_size * sizeof(pval));

			if(temp_arr == NULL)
				break;
			else
				id_list = temp_arr;

			temp_arr = realloc(amount_list, total_size * sizeof(pval));

			if(temp_arr == NULL)
				break;
			else
				amount_list = temp_arr;

			temp_arr = realloc(price_list, total_size * sizeof(pval));

			if(temp_arr == NULL)
				break;
			else
				price_list = temp_arr;
		}

		// Find the entered id
		for(temp_item = inv->first; temp_item != NULL; temp_item = temp_item->next)
		{
			if(temp_item->id == id)
				break;
		}

		// Wrong id entered
		if(temp_item == NULL)
		{
			printf("Invalid ID\n");
			break;
		}

		// Right id entered, now it's time to read amount
		id_list[size] = id;
		printf("Enter amount: ");
		scanf("%u", &amount_list[size]);

		// Update the inventory with taking the bought items
		temp_item->amount -= amount_list[size];
		price_list[size] = amount_list[size] * temp_item->price;
		size++; // Receipt size increases
	}

	// Print receipt
	int i;
	printf("\nReceipt:\n");
	printf(" Qty     Name                   Price\n");

	for(i = 0; i < size; i++)
	{
		printf("%4d     %-20s  %5d\n", amount_list[i],
				get_name(inv, id_list[i]), price_list[i]);
	}

	// Delete receipt list
	free(id_list);
	free(amount_list);
	free(price_list);
}
