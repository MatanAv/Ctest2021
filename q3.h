#pragma once

#define ACCOUNT_BYTES 3
#define FILE_OPEN_ERROR "Error, can not open file"
#define ALLOC_ERROR_MSG "Allocation error"
#define READ_ERROR_MSG "Failed reading from file"

typedef unsigned char BYTE;

typedef struct
{
	int bankCode;
	int branch;
	int number;
}AccountInfo;


void Q3();

AccountInfo* createAccountArrFromFile(const char* fileName, int* pCount);

void printAcountInfo(const AccountInfo* pInfo);
void printAcountInfoArr(const AccountInfo* arr, int count);

