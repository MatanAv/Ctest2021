#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "q1.h"


void Q1()
{

	char str1[] = "This is";
	char str2[] = "A good day";
	char str3[] = "abcdefghijklmnopqrstuvwxyz";
	char** res = NULL;
	int size = 0, longIndex, mostWords;


	res = createArrOfStrings(&size, &longIndex, &mostWords, str1, str2, str3, NULL);
	if (!res)
	{
		puts(ALLOC_ERROR_MSG);
		return;
	}

	printf("\n----- The Strings ------------\n");
	
	for (int i = 0; i < size; i++)
		puts(res[i]);

	printf("\n----- The Longest String ------------\n");

	puts(res[longIndex]);

	printf("\n----- The most words String ------------\n");

	puts(res[mostWords]);

	// free allocations
	for (int i = 0; i < size; i++)
		free(res[i]);
	free(res);
}


char** createArrOfStrings(int* size, int* longIndex, int* mostWords, char* s1, ...)
{
	char* currStr = s1;
	char** strArr = NULL;
	int longest = 0, mostWord = 0, countStr = 0;
	va_list strings;

	va_start(strings, s1);

	while (currStr != NULL)
	{
		countStr++;
		strArr = (char**)realloc(strArr, (sizeof(char*) * (countStr)));
		if (!strArr)
			return NULL;

		strArr[countStr - 1] = (char*)malloc((sizeof(char) * (strlen(currStr) + 1)));
		if (!strArr[countStr - 1])
			return NULL;

		strcpy(strArr[countStr - 1], currStr);

		// Check for most characters
		if (strlen(currStr) > longest)
		{
			longest = strlen(currStr);
			*longIndex = countStr - 1;
		}

		// Check for most words
		int i = 0, space = 0;
		while (currStr[i] != 0)
		{
			if (currStr[i] == ' ')
				space++;
			i++;
		}
		if (space > mostWord)
		{
			mostWord = space;
			*mostWords = countStr - 1;
		}

		currStr = va_arg(strings, char*);
	}

	va_end(strings);

	*size = countStr;
	
	return strArr;
}