#pragma once
#include "GeneralList.h"

#define LEN 9

typedef struct
{
	char*	name;
	char	barcode[LEN + 1];
	float	price;
}Order;

void Q2();

int		initListOfOrder(LIST* plst);
int		initOrderFromUser(Order* pOrder);
int		compareByBarcode(const void* order1, const void* order2);
void	printOrder(const void* order);
void	freeOrder(void* order);