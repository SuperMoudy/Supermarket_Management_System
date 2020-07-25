/*
 * item_list.h
 *
 *  Created on: Jun 12, 2020
 *      Author: SuperMoudy
 */

#ifndef ITEM_LIST_H_
#define ITEM_LIST_H_

struct MarketItem{
	char ItemName[26];
	int ItemID;
	int Amount;
	int Price;
	struct MarketItem *NextItem;
};

struct ReceiptItem{
	int AmountToBuy;
	char ItemName[26];
	int TotalPrice;
	struct ReceiptItem *NextItem;
};

struct MarketItem *InsertItem(struct MarketItem *List);
struct MarketItem *BuyItem(struct MarketItem *list);
struct MarketItem *UpdateItem(struct MarketItem *List);
void PrintItem(struct MarketItem *List);
struct MarketItem *DeleteItem(struct MarketItem *List);

#endif /* ITEM_LIST_H_ */