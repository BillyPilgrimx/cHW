// HW2: Limericks
// Name: Vadim Kobrinsky
// ID: 314257551
// Teacher: Victor
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_NUM 5
#define SPACE_CH ' '
#define SPACE_STR " "
#define DEFAULT_POSITION 0

// prototypes
void InitLimerick(char* myLimerick[]);
char* InsertWord(char* str, int index, char* aword);
char* DeleteWord(char* str, int index);
char* ReplaceWord(char* str, char* word1, char* word2);
int EditLine(char* myLimerick[]);
char* ScanUnlimited();
int CountSpaces(char* str);
int HaveSimilarEndings(char* str1, char* str2, int num);
char* ReplaceWord(char* str, char* word1, char* word2);

void main()
{
	char* limerick[LINE_NUM];
	char text;
	int lineChoice;
	char word1[] = "Brazil";
	char word2[] = "XXX";

	InitLimerick(limerick);
	

	limerick[0] = ReplaceWord(limerick[0], &word1, &word2);
	puts(limerick[0]);
	// EditLine(limerick);

	/*
	puts(limerick[0]);
	limerick[0] = DeleteWord(limerick[0], 3);
	puts(limerick[0]);
	limerick[0] = InsertWord(limerick[0], 3, "man");
	puts(limerick[0]);
	*/
}

void InitLimerick(char* limerick[])
{
	puts("Hello and welcome to the limerick generator program!\nThe common pattern for a limerick is something like this:\n");

	int i;
	for (i = 0; i < LINE_NUM; i++) {
		limerick[i] = "";
	}

	limerick[0] = InsertWord(limerick[0], DEFAULT_POSITION, "There was a man from Brazil");
	printf("1. %s\n", limerick[0]);
	limerick[1] = InsertWord(limerick[1], DEFAULT_POSITION, "Who ...");
	printf("2. %s\n", limerick[1]);
	limerick[2] = InsertWord(limerick[2], DEFAULT_POSITION, "When he/she ...");
	printf("3. %s\n", limerick[2]);
	limerick[3] = InsertWord(limerick[3], DEFAULT_POSITION, "He/She ...");
	printf("4. %s\n", limerick[3]);
	limerick[4] = InsertWord(limerick[4], DEFAULT_POSITION, "...");
	printf("5. %s\n\n", limerick[4]);
}

char* InsertWord(char* str, int index, char* aword)
{
	char* nullStr = "";
	int numberOfWords = CountSpaces(str) + 1;
	if (strcmp(str, nullStr) == 0)
	{
		numberOfWords = 0;
	}
	char* returnStr = NULL;
	char letter;
	int strLength = 0;

	if (numberOfWords < index)
	{
		puts("Invalid index - legal range values for InsertWord are from 0 -> number of words in a line");
		free(str);
		exit(1);
	}

	if (index != 0)
	{

		letter = *str;
		int i = 0;
		while ((letter != SPACE_CH || i < index - 1) && letter != '\0')
		{
			if (letter == SPACE_CH)
			{
				i++;
			}
			returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
			returnStr[strLength] = letter;
			strLength++;
			str++;
			letter = *str;
		}

		returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
		returnStr[strLength] = ' ';
		strLength++;
	}

	letter = *aword;
	while (letter != '\0')
	{
		returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
		returnStr[strLength] = letter;
		strLength++;
		aword++;
		letter = *aword;
	}

	if (index == 0 && (0 < numberOfWords))
	{
		returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
		returnStr[strLength] = ' ';
		strLength++;
	}

	letter = *str;
	while (letter != '\0')
	{
		returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
		returnStr[strLength] = letter;
		strLength++;
		str++;
		letter = *str;
	}

	returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
	returnStr[strLength] = '\0';

	return returnStr;
}

char* DeleteWord(char* str, int index)
{
	char* nullStr = "";
	int numberOfWords = CountSpaces(str) + 1;
	if (strcmp(str, nullStr) == 0)
	{
		numberOfWords = 0;
		puts("Invalid action - cannot delete a word from a non initiated string");
		free(str);
		exit(1);
	}
	char* returnStr = NULL;
	char letter;
	int strLength = 0;

	if (numberOfWords < index)
	{
		puts("Invalid index - legal range values for DeleteWord are from 0 -> number of words in a line");
		free(str);
		exit(1);
	}

	if (index != 0)
	{

		letter = *str;
		int i = 0;
		while ((letter != SPACE_CH || i < index - 1) && letter != '\0')
		{
			if (letter == SPACE_CH)
			{
				i++;
			}
			returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
			returnStr[strLength] = letter;
			strLength++;
			str++;
			letter = *str;
		}
	}

	str++;
	letter = *str;
	while (letter != SPACE_CH)
	{
		// in case we deleting the last word
		if (letter == '\0')
		{
			returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
			returnStr[strLength] = '\0';
			return returnStr;
		}
		str++;
		letter = *str;
	}


	if (index != 0 && (0 < numberOfWords))
	{
		returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
		returnStr[strLength] = ' ';
		strLength++;
	}

	str++;
	letter = *str;
	while (letter != '\0')
	{
		returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
		returnStr[strLength] = letter;
		strLength++;
		str++;
		letter = *str;
	}

	returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
	returnStr[strLength] = '\0';

	return returnStr;
}

char* ReplaceWord(char* str, char* word1, char* word2)
{
	char* returnStr = NULL;
	char* subStringAfterCuttingOut = strstr(str, word1);
	int wordsNumInFirstPart;

	// in case we want to substitute the first word
	if (str == subStringAfterCuttingOut)
	{
		returnStr = DeleteWord(str, DEFAULT_POSITION);
		returnStr = InsertWord(returnStr, DEFAULT_POSITION, word2);

		return returnStr;
	}


	// adding a space before the word we would like to search for better searching...
	char tmpLetter;
	int tmpLength = 0;
	char* _word1 = NULL;

	_word1 = (char*)realloc(_word1, sizeof(char) * (tmpLength + 1));
	_word1[tmpLength] = ' ';
	tmpLength++;
	while (*word1 != '\0')
	{
		_word1 = (char*)realloc(_word1, sizeof(char) * (tmpLength + 1));
		_word1[tmpLength] = *word1;
		tmpLength++;
		word1++;
	}
	_word1 = (char*)realloc(_word1, sizeof(char) * (tmpLength + 1));
	_word1[tmpLength] = '\0';
	tmpLength++;
	
	char letter;
	subStringAfterCuttingOut = strstr(str, _word1);
	char* secondPart = DeleteWord(subStringAfterCuttingOut, DEFAULT_POSITION);
	
	int strLength = 0;
	letter = *str;
	int i = 0;
	while (str < subStringAfterCuttingOut)
	{
		returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
		returnStr[strLength] = letter;
		strLength++;
		str++;
		letter = *str;
	}
	returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
	returnStr[strLength] = '\0';
	strLength++;

	wordsNumInFirstPart = CountSpaces(returnStr);
	returnStr = InsertWord(returnStr, wordsNumInFirstPart + 1, word2);

	wordsNumInFirstPart = CountSpaces(returnStr);
	returnStr = InsertWord(returnStr, wordsNumInFirstPart + 1, secondPart);

	return returnStr;
}

int EditLine(char* myLimerick[])
{
	int flag = 1;
	char choice;
	int choiceNum;

	while (flag != 0)
	{
		flag = 0;

		printf("If you like to edit a line please enter which line would you like to edit (1-5)\nPress 9 for finding similar endings or 0 for EXIT: ");
		scanf(" %c", &choice);

		if (choice == '0')
		{
			puts("Thank you and see you next time!");
			exit(0);
		}
		else if (choice == '9')
		{

		}
		else if (choice < '1' || '5' < choice)
		{
			flag = 1;
			printf("Invalid input, please try again...\n");
		}

	}

	choiceNum = ((int)choice) - 48;
	return choiceNum;
}

char* ScanUnlimited()
{
	char* str = NULL;
	char letter;
	int length = 0;

	scanf("%c", &letter);
	while (letter != 13)
	{
		str = (char*)realloc(str, sizeof(char) * (length + 1));
		str[length] = letter;
		length++;
		scanf("%c", &letter);
	}
	str = (char*)realloc(str, sizeof(char) * (length + 1));
	str[length] = '\0';

	return str;
}

int CountSpaces(char* str)
{
	int counter = 0;
	while (*str != '\0')
	{
		if (*str == SPACE_CH)
		{
			counter++;
		}
		str++;
	}
	return counter;
}

int CountCharacters(char* str)
{
	int counter = 0;
	while (*str != '\0')
	{
		counter++;
		str++;
	}
	return counter;
}







