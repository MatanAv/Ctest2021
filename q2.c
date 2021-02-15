#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "q2.h"


void Q2()
{
	LIST lst;

	if (!initListOfOrder(&lst))
	{
		puts("Error");
		return;
	}

	printf("\n ------- The list ------------\n");

	L_print(&lst, printOrder);

	printf("\n ------- The list after delete last ------------\n");

	// Delete last order
	NODE* tmp = lst.head.next;
	NODE* prev = lst.head.next;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		if (prev->next != tmp)
			prev = prev->next;
	}
	L_delete(prev, freeOrder);

	L_print(&lst, printOrder);

	// Find by barcode
	Order toFind;
	NODE* found;

	printf("Please enter the barcode to be found: ");
	scanf("%s", toFind.barcode);			// Assuming that a valid input has been inserted
	found = L_find(lst.head.next, &toFind, compareByBarcode);
	if (!found)
		puts("Not found");
	else
	{
		Order* ordFound = (Order*)found->key;
		printOrder(ordFound);
	}

	L_free(&lst, freeOrder);
}

int		compareByBarcode(const void* order1, const void* order2)
{
	Order* o1 = (Order*)order1;
	Order* o2 = (Order*)order2;
	return strcmp(o1->barcode, o2->barcode);
}

void	printOrder(void* order)
{
	Order* ord = (Order*)order;
	printf("%s\t%s\t%.2f\n", ord->name, ord->barcode, ord->price);
}

void	freeOrder(const void* order)
{
	Order* ord = (Order*)order;
	free(ord->name);
	free(ord);
}

int	initListOfOrder(LIST* plst)
{
	L_init(plst);
	int count;
	Order* pTemp;
	NODE* pN = &plst->head;

	printf("How many orders in list\n");
	scanf("%d", &count);

	for (int i = 0; i < count; i++)
	{
		pTemp = (Order*)malloc(sizeof(Order));
		if (!pTemp)
			return 0;
		initOrderFromUser(pTemp);
		pN = L_insert(pN, pTemp);
	}

	return 1;
}

int		initOrderFromUser(Order* pOrder)
{
	printf("Please enter order name, barcode (%d chars) and price\n",LEN);
	char temp[255];
	scanf("%s %s %f", temp, pOrder->barcode, &pOrder->price);
	pOrder->name = _strdup(temp);
	if (!pOrder->name)
		return 0;
	return 1;
}