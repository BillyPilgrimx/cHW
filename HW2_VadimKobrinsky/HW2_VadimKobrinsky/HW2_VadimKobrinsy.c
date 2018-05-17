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
char* InsertWord(char* str, int index, char* aword);
char* DeleteWord(char* str, int index);
char* ReplaceWord(char* str, char* word1, char* word2);
int HaveSimilarEndings(char* str1, char* str2, int num);

void initSampleLimerick(char* myLimerick[]);
void InitMenu(char* limerick[]);
char* ScanUnlimited();
int CountSpaces(char* str);

void main()
{
	char* limerick[LINE_NUM];

	initSampleLimerick(limerick);
	InitMenu(limerick);
}

void initSampleLimerick(char* limerick[])
{
	puts("Hello and welcome to the limerick generator program!\nThe common pattern for a limerick is something like this:");
	int i;
	for (i = 0; i < LINE_NUM; i++) {
		limerick[i] = "";
	}
	limerick[0] = InsertWord(limerick[0], DEFAULT_POSITION, "There was a ... from ...");
	limerick[1] = InsertWord(limerick[1], DEFAULT_POSITION, "Who was ... like a ...");
	limerick[2] = InsertWord(limerick[2], DEFAULT_POSITION, "When he has ...");
	limerick[3] = InsertWord(limerick[3], DEFAULT_POSITION, "He ...");
	limerick[4] = InsertWord(limerick[4], DEFAULT_POSITION, "Thats funny ...");
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

void InitMenu(char* limerick[])
{
	char* text1;
	char* text2;
	int choice;

	int flag = 1;

	do
	{
		printf("\n");
		int i;
		for (i = 0; i < LINE_NUM; i++)
		{
			puts(limerick[i]);
		}
		puts("\nWhich line would you like to edit (1-5) or press 0 to count the rhymes and exit: ");
		scanf("%d", &choice);

		flag = 0;
		switch (choice)
		{
		case 1:
			flag = 1;
			puts(limerick[choice - 1]);
			puts("\nPlease enter which word you would like to substitute: ");
			text1 = ScanUnlimited();
			puts("\nwith which word ? (Suggestions: man, boy, lad, dog - Heaven, Brazil, Moon, Japan): ");
			text2 = ScanUnlimited();
			limerick[choice - 1] = ReplaceWord(limerick[choice - 1], text1, text2);
			break;

		case 2:
			flag = 1;
			puts(limerick[choice - 1]);
			puts("\nPlease enter which word you would like to substitute: ");
			text1 = ScanUnlimited();
			puts("\nwith which word ? (Suggestions: eating, running, sleeping, swinging, weeping - horse, stone, girl, bear, indian, mouse, mill): ");
			text2 = ScanUnlimited();
			limerick[choice - 1] = ReplaceWord(limerick[choice - 1], text1, text2);
			break;

		case 3:
			flag = 1;
			puts(limerick[choice - 1]);
			puts("\nPlease enter which word you would like to substitute: ");
			text1 = ScanUnlimited();
			puts("\nwith which word ? (Suggestions: pointed at me, has awaken, been mistaken, felt shaken, talked without a break): ");
			text2 = ScanUnlimited();
			limerick[choice - 1] = ReplaceWord(limerick[choice - 1], text1, text2);
			break;

		case 4:
			flag = 1;
			puts(limerick[choice - 1]);
			puts("\nPlease enter which word you would like to substitute: ");
			text1 = ScanUnlimited();
			puts("\nwith which word ? (Suggestions: been attacked by a cat , worn a hat, felt shame and regret, looked sad and bleak): ");
			text2 = ScanUnlimited();
			limerick[choice - 1] = ReplaceWord(limerick[choice - 1], text1, text2);
			break;
			
		case 5:
			flag = 1;
			puts(limerick[choice - 1]);
			puts("\nPlease enter which word you would like to substitute: ");
			text1 = ScanUnlimited();
			puts("\nwith which word ? (Suggestions: he sounded like an earthquake, how he met his own destiny, he never got married): ");
			text2 = ScanUnlimited();
			limerick[choice - 1] = ReplaceWord(limerick[choice - 1], text1, text2);
			break;
			
		case 0:
			puts("\nCounting rhymes...");
			break;

		}  
	} while (flag != 0);
}

char* ScanUnlimited()
{
	char* str = NULL;
	char letter;
	int length = 0;

	scanf(" %c", &letter);
	while (letter != '\n')
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







