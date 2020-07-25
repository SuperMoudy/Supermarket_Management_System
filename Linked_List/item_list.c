/*
 * item_list.c
 *
 *  Created on: Jun 12, 2020
 *      Author: SuperMoudy
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "item_list.h"

struct MarketItem *InsertItem(struct MarketItem *List){
	struct MarketItem *NewItem = malloc(sizeof(struct MarketItem));

	if(NewItem == NULL){
		printf("Can't insert more items\n");
		exit(EXIT_FAILURE);
	}

	printf("Please, enter the item name: ");
	gets((*NewItem).ItemName);

	struct MarketItem *TempItem = List, *PrevItem = NULL;

	while(TempItem != NULL){
		if(!strcmp((*TempItem).ItemName, (*NewItem).ItemName)){
			printf("Item already in the market\n");
			free(NewItem);
			return List;
		}
		else{
			PrevItem = TempItem;
			TempItem = (*TempItem).NextItem;
		}
	}

	printf("Please, enter the item ID: ");
	scanf("%d", &(*NewItem).ItemID);

	printf("Please, enter the item amount: ");
	scanf("%d", &(*NewItem).Amount);

	printf("Please, enter the item price: ");
	scanf("%d", &(*NewItem).Price);

	(*NewItem).NextItem = NULL;

	if(PrevItem != NULL)
		(*PrevItem).NextItem = NewItem;
	else
		List = NewItem;

	return List;
}

struct MarketItem *BuyItem(struct MarketItem *List){
	int ID;
	struct ReceiptItem *Receipt = NULL, *LastItem, *TempItem;
	struct MarketItem *ItemToBuy;

	printf("Please, enter item ID: ");
	scanf("%d", &ID);

	while(ID > 0){
		ItemToBuy = List;

		while(ItemToBuy != NULL){
			if((*ItemToBuy).ItemID == ID)
				break;

			ItemToBuy = (*ItemToBuy).NextItem;
		}


		if(ItemToBuy == NULL){
			printf("Item is not in the list, please try again\n");
		}
		else{
			struct ReceiptItem *NewItem = malloc(sizeof(struct ReceiptItem));

			if(NewItem == NULL){
				printf("This list is too long, please try a shorter list\n");
				return List;
			}

			printf("Please, enter item amount: ");
			scanf("%d", &(*NewItem).AmountToBuy);
			(*NewItem).TotalPrice = (*NewItem).AmountToBuy * (*ItemToBuy).Price;
			strcpy((*NewItem).ItemName, (*ItemToBuy).ItemName);
			(*NewItem).NextItem = NULL;

			(*ItemToBuy).Amount -= (*NewItem).AmountToBuy;

			if(Receipt == NULL){
				Receipt = NewItem;
				LastItem = NewItem;
			}
			else{
				(*LastItem).NextItem = NewItem;
				LastItem = (*LastItem).NextItem;
			}
		}

		printf("Please, enter item ID: ");
		scanf("%d", &ID);
	}


	// Printing list
	TempItem = Receipt;
	printf("Amount");
	printf("   ");
	printf("Item Name");
	printf("                   ");
	printf("Price\n");

	while(TempItem != NULL){
		printf("%5d", (*TempItem).AmountToBuy);
		printf("    ");
		printf("%-25s", (*TempItem).ItemName);
		printf("  ");
		printf("%5d\n", (*TempItem).TotalPrice);
		TempItem = (*TempItem).NextItem;
	}

	// Deleting List
	while(Receipt != NULL){
		TempItem = Receipt;
		Receipt = (*Receipt).NextItem;
		free(TempItem);
	}

	return List;
}

struct MarketItem *UpdateItem(struct MarketItem *List){
	char ItemName[26], Choice;
	struct MarketItem *TempItem = List;

	printf("Please, enter the name of the item: ");
	gets(ItemName);

	while(TempItem != NULL){
		if(!strcmp((*TempItem).ItemName, ItemName))
			break;

		TempItem = (*TempItem).NextItem;
	}

	if(TempItem == NULL){
		printf("Item is not in the market list\n");
		return List;
	}

	printf("Do you want to update ID? (y/n) ");
	scanf(" %c", &Choice);

	if(Choice == 'y'){
		printf("Please, enter the new ID: ");
		scanf("%d", &(*TempItem).ItemID);
	}

	printf("Do you want to update amount? (y/n) ");
	scanf(" %c", &Choice);

	if(Choice == 'y'){
		printf("Please, enter the new amount: ");
		scanf("%d", &(*TempItem).Amount);
	}


	printf("Do you want to update price? (y/n) ");
	scanf(" %c", &Choice);

	if(Choice == 'y'){
		printf("Please, enter the new price: ");
		scanf("%d", &(*TempItem).Price);
	}

	return List;
}

void PrintItem(struct MarketItem *List){
	printf("Item Name");
	printf("                   ");
	printf("Item ID");
	printf("   ");
	printf("Amount");
	printf("   ");
	printf("Price\n");

	while(List != NULL){
		printf("%-25s", (*List).ItemName);
		printf("   ");
		printf("%5d", (*List).ItemID);
		printf("    ");
		printf("%5d", (*List).Amount);
		printf("    ");
		printf("%5d\n", (*List).Price);
		List = (*List).NextItem;
	}
}

struct MarketItem *DeleteItem(struct MarketItem *List){
	struct MarketItem *TempItem = List, *PrevItem = NULL;
	char ItemName[26];

	if(List == NULL){
		printf("No items available in the market to delete\n");
		return NULL;
	}

	printf("Please, enter the item name: ");
	gets(ItemName);

	while(TempItem != NULL){
		if(!strcmp((*TempItem).ItemName, ItemName))
			break;

		PrevItem = TempItem;
		TempItem = (*TempItem).NextItem;
	}

	if(TempItem == NULL){
		printf("Item is not in the market\n");
		return List;
	}

	if(PrevItem == NULL)
		List = (*List).NextItem;
	else if((*TempItem).NextItem == NULL)
		(*PrevItem).NextItem = NULL;
	else
		(*PrevItem).NextItem = (*TempItem).NextItem;

	free(TempItem);
	return List;
}
