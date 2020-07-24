/*
 * accounts.h
 *
 *  Created on: Jun 11, 2020
 *      Author: SuperMoudy
 */

#ifndef ACCOUNTS_H_
#define ACCOUNTS_H_

// Macros
#define NAME_LEN 20

// Account structure
typedef struct
{
	char name[NAME_LEN + 1];
	int id;
	int amount;
	int price;
} Item;


// Basic account functions
void insert_account(Item *account, int *size, int *max_size);
void pay_receipt(Item *account, int size);
void modify_account(Item *account, int size);
void print_all(Item *account, int size);
void delete_account(Item *account, int *size);
int id_exists(Item *account, int size, int id);


#endif /* ACCOUNTS_H_ */

