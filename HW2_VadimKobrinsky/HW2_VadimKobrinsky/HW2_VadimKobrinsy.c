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
void InitLimerickProg(char* myLimerick[]);
char* InsertWord(char* str, int index, char* aword);
char* DeleteWord(char* str, int index);
char* ReplaceWord(char* str, char* word1, char* word2);
void InitMenu(char* limerick[]);
char* ScanUnlimited();
int CountSpaces(char* str);
int HaveSimilarEndings(char* str1, char* str2, int num);
char* ReplaceWord(char* str, char* word1, char* word2);

void main()
{
	char* limerick[LINE_NUM];

	InitLimerickProg(limerick);
	InitMenu(limerick);

}

void InitLimerickProg(char* limerick[])
{
	puts("Hello and welcome to the limerick generator program!\nThe common pattern for a limerick is something like this:\n");

	int i;
	for (i = 0; i < LINE_NUM; i++) {
		limerick[i] = "";
	}

	limerick[0] = InsertWord(limerick[0], DEFAULT_POSITION, "There was a ... from ...");
	printf("1. %s\n", limerick[0]);
	limerick[1] = InsertWord(limerick[1], DEFAULT_POSITION, "Who was ... like a ...");
	printf("2. %s\n", limerick[1]);
	limerick[2] = InsertWord(limerick[2], DEFAULT_POSITION, "When he has ...");
	printf("3. %s\n", limerick[2]);
	limerick[3] = InsertWord(limerick[3], DEFAULT_POSITION, "He ...");
	printf("4. %s\n", limerick[3]);
	limerick[4] = InsertWord(limerick[4], DEFAULT_POSITION, "Thats funny ...");
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
	int flag = 1;
	char choice;
	int choiceNum;

	while (flag != 0)
	{
		flag = 0;
		printf("You are in edit mode please select a line you would like to edit (1-5)\nPress 8 to exit edit mode and show the whole limerick\nPress 9 after editing the lines for finding similar endings\nPress 0 at anytime for EXIT: ");
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
	printf("\n");


	int flag2 = 1;

	while (flag2 != 0)
	{
		flag2 = 0;
		switch (choiceNum)
		{
		case 1:
			flag2 = 1;
			printf("You chose to edit line number: %d\n\n", choiceNum);
			puts(limerick[0]);

			puts("Please enter a word to substitue the first (...) - usually a character\n");
			puts("Suggestions: man, boy, lad, old man, dog");
			limerick[0] = ReplaceWord(limerick[0], "...", ScanUnlimited());
			puts(limerick[0]);

			puts("Please enter a word to substitue the second (...) - usually a place\n");
			puts("Suggestions: Brazil, Germany, Moon, Heaven, Japan");
			limerick[0] = ReplaceWord(limerick[0], "...", ScanUnlimited());
			puts(limerick[0]);
			printf("\nWhich line to edit next (zero for exit): ");
			scanf("%d", &choiceNum);
			break;

		case 2:
			flag2 = 1;
			printf("You chose to edit line number: %d\n\n", choiceNum);
			puts(limerick[1]);

			puts("Please enter a word to substitue the first (...) - usually a verb\n");
			puts("Suggestions: eating, running, sleeping, programing, weeping");
			limerick[1] = ReplaceWord(limerick[1], "...", ScanUnlimited());
			puts(limerick[1]);

			puts("Please enter a word to substitue the second (...) - usually a noun\n");
			puts("Suggestions: stone, girl, bear, indian, mouse");
			limerick[1] = ReplaceWord(limerick[1], "...", ScanUnlimited());
			puts(limerick[1]);
			printf("\nWhich line to edit next (zero for exit): ");
			scanf("%d", &choiceNum);
			break;

		case 3:
			flag2 = 1;
			printf("You chose to edit line number: %d\n\n", choiceNum);
			puts(limerick[2]);

			puts("Please enter a pair of words to substitue the (...) - usually a verb\n");
			puts("Suggestions: has awaken, been mistaken, felt shaken, talked without a break");
			limerick[2] = ReplaceWord(limerick[2], "...", ScanUnlimited());
			puts(limerick[2]);
			printf("\nWhich line to edit next (zero for exit): ");
			scanf("%d", &choiceNum);
			break;
			

		case 4:
			flag2 = 1;
			puts("Please enter a pair of words to substitue the (...) - usually a adverb\n");
			puts("Suggestions: been attacked by a cat , worn a hat, felt shame and regret");
			limerick[3] = ReplaceWord(limerick[3], "...", ScanUnlimited());
			puts(limerick[3]);
			printf("\nWhich line to edit next (zero for exit): ");
			scanf("%d", &choiceNum);
			break;

		case 5:
			flag2 = 1;
			puts("Please enter a sentence to substitue the (...) - usually a closing sentence\n");
			puts("Suggestions: he sounded like an earthquake, how he met his own destiny");
			limerick[3] = ReplaceWord(limerick[3], "...", ScanUnlimited());
			puts(limerick[3]);
			printf("\nWhich line to edit next (zero for exit): ");
			scanf("%d", &choiceNum);
			break;

		case 0:
			break;

		}
	}
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







