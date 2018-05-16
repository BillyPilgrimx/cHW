// HW2: Limericks
// Name: Vadim Kobrinsky
// ID: 314257551
// Teacher: Victor
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_NUM 5
#define SPACE ' '

// prototypes
void Welcome(char* exampleLimrick[]);
void initDynamicArrays(char* myLimerick[]);
int EditLine(char* myLimerick[]);
char* ReadUnlimited();

int HaveSimilarEndings(char* str1, char* str2, int num);
char* DeleteWord(char* str, int index);
char* InsertWord(char* str, int index);
char* ReplaceWord(char* str, char* word1, char* word2);

void main()
{
	char* exampleLimrick[LINE_NUM];
	char* myLimerick[LINE_NUM];
	char text;
	int lineChoice;

	Welcome(exampleLimrick);
	initDynamicArrays(myLimerick);
	lineChoice = EditLine(myLimerick);




}

void Welcome(char* exampleLimrick[]) {

	char* welcomeLimerick[LINE_NUM];
	welcomeLimerick[0] = "There was a ... from ... ";
	welcomeLimerick[1] = "Who ... ";
	welcomeLimerick[2] = "When he/she ... ";
	welcomeLimerick[3] = "He/She ...";
	welcomeLimerick[4] = "... ";

	printf("Hello and welcome to the limerick generator program!\nThe common pattern for a limerick is something like this:\n");
	int i;
	for (i = 0; i < LINE_NUM; i++)
	{
		printf("%d. %s\n", i + 1, welcomeLimerick[i]);
	}
}

void initDynamicArrays(char* myLimerick[])
{
	int i;
	for (i = 0; i < LINE_NUM; i++) {
		myLimerick[i] = NULL;
	}



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
		else if (choice < 49 || 53 < choice)
		{
			flag = 1;
			printf("Invalid input, please try again...\n");
		}
		
	}

	choiceNum = ((int)choice) - 48;
	// printf("You editing the line: %s", *limerick[choice]);

	switch (choice)
	{
	case '1': 
		break;

	case '2':
		break;

	case '3':
		break;

	case '4':
		break;

	case '5':
		break;

	default:
		break;
	}

	return choiceNum;
}

char* ReadUnlimited()
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
		if (*str == SPACE)
		{
			counter++;
		}
		str++;
	}
	return counter;
}

char* DeleteWord(char* str, int index)
{
	char* tmpStr;


}


char* InsertWord(char* str, int index)
{
	char* tmpStr = NULL;





}

