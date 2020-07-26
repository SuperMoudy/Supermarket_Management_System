/*
 * market.h
 *
 *  Created on: Jun 13, 2020
 *      Author: SuperMoudy
 */

#ifndef MARKET_H_
#define MARKET_H_

#include <stdbool.h>

// Abstracting the database to be easily-used
typedef struct market_database *Market_DB;

// pval is shorthand for positive value
typedef unsigned int pval;

// Create a new inventory
Market_DB create(void);

// Is the inventory empty?
bool is_empty(Market_DB inv);

// Add a new item to the inventory
void add_item(Market_DB inv);

// Remove an item in the inventory
void remove_item(Market_DB inv);

// Print the whole inventory
void print_list(Market_DB inv);

// Modify an item in the inventory
void modify_item(Market_DB inv);

// Scan the items bought to get the bill
void scan_list(Market_DB inv);

#endif /* MARKET_H_ */
