/*
 * market.c
 *
 *  Created on: Jun 12, 2020
 *      Author: SuperMoudy
 */

#include <stdio.h>
#include <string.h>
#include "item_list.h"

int main(void){
	struct MarketItem *ItemList = NULL;
	char SetPassword[26] = "market2020", Password[26], Operation[7];
	int i;

	for(i = 0; i < 3; i++){
		printf("Please, enter the Password: ");
		gets(Password);

		if(!strcmp(Password, SetPassword))
			break;
		else
			printf("Wrong Password\n\n");

		if(i == 2)
			return 0;
	}

	while(1){
		printf("\n");
		printf("Please, enter an operation: ");
		scanf("%s", Operation);
		getchar();

		if(!strcmp(Operation, "Insert")){
			ItemList = InsertItem(ItemList);
		}
		else if(!strcmp(Operation, "Buy")){
			ItemList = BuyItem(ItemList);
		}
		else if(!strcmp(Operation, "Update")){
			ItemList = UpdateItem(ItemList);
		}
		else if(!strcmp(Operation, "Print")){
			PrintItem(ItemList);
		}
		else if(!strcmp(Operation, "Delete")){
			ItemList = DeleteItem(ItemList);
		}
		else if(!strcmp(Operation, "Exit")){
			return 0;
		}
		else{
			printf("Invalid operation, try again\n");
		}
	}

	return 0;
}
