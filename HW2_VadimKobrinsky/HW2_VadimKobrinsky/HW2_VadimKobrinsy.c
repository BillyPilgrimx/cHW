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
#define BSLSH_0 '\0'
#define NULL_STR ""
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

char* InsertWord(char* str, int index, char* aword)
{
	char* nullStr = NULL_STR;
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
		while ((letter != SPACE_CH || i < index - 1) && letter != BSLSH_0)
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
		returnStr[strLength] = SPACE_CH;
		strLength++;
	}

	letter = *aword;
	while (letter != BSLSH_0)
	{
		returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
		returnStr[strLength] = letter;
		strLength++;
		aword++;
		letter = *aword;
	}

	//if (index == 0 && (0 < numberOfWords))
	if (numberOfWords < index)
	{
		returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
		returnStr[strLength] = SPACE_CH;
		strLength++;
	}

	letter = *str;
	while (letter != BSLSH_0)
	{
		returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
		returnStr[strLength] = letter;
		strLength++;
		str++;
		letter = *str;
	}

	returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
	returnStr[strLength] = BSLSH_0;

	return returnStr;
}

char* DeleteWord(char* str, int index)
{
	char* nullStr = NULL_STR;
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
		while ((letter != SPACE_CH || i < index - 1) && letter != BSLSH_0)
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
		if (letter == BSLSH_0)
		{
			returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
			returnStr[strLength] = BSLSH_0;
			return returnStr;
		}
		str++;
		letter = *str;
	}


	if (index != 0 && (0 < numberOfWords))
	{
		returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
		returnStr[strLength] = SPACE_CH;
		strLength++;
	}

	str++;
	letter = *str;
	while (letter != BSLSH_0)
	{
		returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
		returnStr[strLength] = letter;
		strLength++;
		str++;
		letter = *str;
	}

	returnStr = (char*)realloc(returnStr, sizeof(char) * (strLength + 1));
	returnStr[strLength] = BSLSH_0;

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
	_word1[tmpLength] = SPACE_CH;
	tmpLength++;
	while (*word1 != BSLSH_0)
	{
		_word1 = (char*)realloc(_word1, sizeof(char) * (tmpLength + 1));
		_word1[tmpLength] = *word1;
		tmpLength++;
		word1++;
	}
	_word1 = (char*)realloc(_word1, sizeof(char) * (tmpLength + 1));
	_word1[tmpLength] = BSLSH_0;
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
	returnStr[strLength] = BSLSH_0;
	strLength++;

	wordsNumInFirstPart = CountSpaces(returnStr);
	returnStr = InsertWord(returnStr, wordsNumInFirstPart + 1, word2);

	if (0 < CountSpaces(secondPart)) 
	{
		wordsNumInFirstPart = CountSpaces(returnStr);
		returnStr = InsertWord(returnStr, wordsNumInFirstPart + 1, secondPart);
	}

	return returnStr;
}

int HaveSimilarEndings(char* str1, char* str2, int num)
{
	char* tmpStr1;
	char* tmpStr2;
	int i;

	while (*str1 != BSLSH_0)
	{
		str1++;
	}

	for (i = 0; i < num; i++)
	{
		str1--;
	}

	while (*str2 != BSLSH_0)
	{
		str2++;
	}

	for (i = 0; i < num; i++)
	{
		str2--;
	}


	int result = 1;
	for (i = 0; i < num; i++)
	{
		if (*str1 != *str2)
		{
			result = 0;
		}
		str1++;
		str2++;
	}


	for (i = 0; i < num; i++)
	{

	}


	return result;
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

	/*
	limerick[0] = InsertWord(limerick[0], DEFAULT_POSITION, "There was a man from Brazil");
	limerick[1] = InsertWord(limerick[1], DEFAULT_POSITION, "Who was looking like a pill");
	limerick[2] = InsertWord(limerick[2], DEFAULT_POSITION, "When he has having Japan");
	limerick[3] = InsertWord(limerick[3], DEFAULT_POSITION, "He was smelling like clown");
	limerick[4] = InsertWord(limerick[4], DEFAULT_POSITION, "Thats funny ...");
	*/
}

void InitMenu(char* limerick[])
{
	char* text1 = NULL;
	char* text2 = NULL;
	int choice;
	int charsToCompare;

	int flag = 1;
	char innerFlag = 'y';

	do
	{
		// print the whole limerick
		printf("\n");
		int i;
		for (i = 0; i < LINE_NUM; i++)
		{
			puts(limerick[i]);
		}

		// select a line to edit menu + get input
		printf("\nEnter which line you would like to edit (1-5) or press 0 to count the rhymes and exit\nFor exit without counting rhymes press any other character: ");
		scanf("%d", &choice);
		printf("\n");

		// show the selected line
		if (0 < choice && choice < 6)
		{
			puts(limerick[choice - 1]);
			printf("\nPlease enter the WORD you would like to SUBSTITUTE: ");
			text1 = ScanUnlimited();
			printf("Enter the WORD to substitute WITH? ");
		}

		// different hints for eack line 
		switch (choice)
		{
		case 1:
			printf("(Suggestions - First word: man, boy, lad, dog - Second word: Heaven, Brazil, Moon, Japan): ");
			break;

		case 2:
			printf("(Suggestions - First word: staring, eating, running, sleeping, swinging, weeping - Second word: raven, automobile, girl, bear, Spartan, mouse, mill, baffoon): ");
			break;

		case 3:
			printf("(Suggestions: pointed at me, has awaken, been mistaken, felt shaken, talked without a break): ");
			break;

		case 4:
			printf("(Suggestions: been attacked by a cat , worn a hat, felt shame and regret, looked sad and bleak): ");
			break;

		case 5:
			puts("(Suggestions: he sounded like an earthquake, how he met his own destiny, he never got married): ");
			break;

			// the rhyme check with the HaveSimilarEndings() func happens here - in case 0
		case 0:
			flag = 1;
			while (innerFlag != 'n')
			{
				if (innerFlag != 'y' && innerFlag != 'n')
				{
					printf("\nInvalid input, try again...");
					printf("\nDo you want to try and compare different number of ending characters? (y/n): ");
				}
				else
				{
					innerFlag = 'y';

					printf("\nHow many characters would you like to check for rhymes: ");
					scanf("%d", &charsToCompare);
					printf("\nComparing the last %d ending characters of lines 1-2 and 3-4\n", charsToCompare);
					int do_lines_1_2_rhyme = HaveSimilarEndings(limerick[DEFAULT_POSITION], limerick[DEFAULT_POSITION + 1], charsToCompare);
					int do_lines_3_4_rhyme = HaveSimilarEndings(limerick[DEFAULT_POSITION + 2], limerick[DEFAULT_POSITION + 3], charsToCompare);
					printf("\nThe number of rhymes is: %d", do_lines_1_2_rhyme + do_lines_3_4_rhyme);
					printf("\nDo you want to try and compare different number of ending characters? (y/n): ");
				}

				scanf(" %c", &innerFlag);
			}

			printf("\nTHANK YOU AND SEE YOU NEXT TIME !!!\n");
			exit(0);
			break;

		default:
			printf("\nTHANK YOU AND SEE YOU NEXT TIME !!!\n");
			exit(0);
			break;
		}

		// scan the replacing word and execute ReplaceWord func
		if (0 < choice && choice < 6 && text1 != NULL)
		{
			text2 = ScanUnlimited();
			limerick[choice - 1] = ReplaceWord(limerick[choice - 1], text1, text2);
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
	str[length] = BSLSH_0;

	return str;
}

int CountSpaces(char* str)
{
	int counter = 0;
	while (*str != BSLSH_0)
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
	while (*str != BSLSH_0)
	{
		counter++;
		str++;
	}
	return counter;
}







