#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "q3.h"

#define FILE_NAME "accounts_comp.bin"
//#define FILE_NAME "accounts.bin"

void Q3()
{

	int count;

	AccountInfo* arr = createAccountArrFromFile(FILE_NAME,&count);

	printf("\n\n--------- after read ----------\n\n");
	printAcountInfoArr(arr, count);

	free(arr);

}

AccountInfo* createAccountArrFromFile(const char* fileName, int* pCount)
{
	FILE* fp = fopen(fileName, "rb");
	if (!fp)
	{
		puts(FILE_OPEN_ERROR);
		return NULL;
	}

	BYTE size;
	// Getting size of accounts
	if (fread(&size, sizeof(BYTE), 1, fp) != 1)
	{
		puts(READ_ERROR_MSG);
		return NULL;
	}
	*pCount = size;

	AccountInfo* accArr = (AccountInfo*)malloc((sizeof(AccountInfo) * size));
	if (!accArr)
	{
		puts(ALLOC_ERROR_MSG);
		return NULL;
	}

	BYTE byte[ACCOUNT_BYTES];

	for (int i = 0; i < size; i++)
	{
		if (fread(byte, sizeof(BYTE), 3, fp) != 3)		// Reading Account
		{
			puts(READ_ERROR_MSG);
			return NULL;
		}

		accArr[i].bankCode = (byte[0] & 0xE0) >> 5;
		accArr[i].branch = ((byte[1] & 0xF0) >> 4) | ((byte[0] & 0xF) << 4 ) | ((byte[0] & 0x10) << 4);
		accArr[i].number = byte[2] | ((byte[1] & 0xF) << 8);
	}

	fclose(fp);
	return accArr;
}

void printAcountInfo(const AccountInfo* pInfo)
{
	printf("Account: bank %d branch %d number %d\n", pInfo->bankCode, pInfo->branch, pInfo->number);
	
}

void printAcountInfoArr(const AccountInfo* arr, int count)
{
	printf("There are %d accounts\n", count);
	for (int i = 0; i < count; i++)
		printAcountInfo(&arr[i]);
	printf("\n");
}
