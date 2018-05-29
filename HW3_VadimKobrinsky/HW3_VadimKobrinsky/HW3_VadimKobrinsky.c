// Name: Vadim Kobrinsky
// ID: 314257551
// Teacher: Victor
// Task: Soccer
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Constants
#define NAME_LENGTH 40

// Type definitions of structs
typedef struct game
{
	char name1[NAME_LENGTH];
	char name2[NAME_LENGTH];
	int goals1;
	int goals2;
} GAME;

typedef struct game_node
{
	GAME agame;
	struct game_node* next;
} GAME_NODE;

typedef struct team
{
	char name[NAME_LENGTH];
	int games_played;
	int wins;
	int draws;
	int losses;
	GAME_NODE* games;
} TEAM;

// Prototypes
GAME* ReadGames(int *pngames);
GAME ReadGame();
void PrintGames(GAME games[], int* pngames); // helper function

TEAM* FillTable(int *pnum_teams, GAME all_games[], int num_games);
TEAM* PrepareTable(int* tsize, GAME all_games[], int num_games);
PrintNamesArray(char** names, int num_names); // helper function
void PrintTable(TEAM* table, int num_teams);

// Main
void main()
{
	GAME* all_games = NULL;
	TEAM* table = NULL;
	int num_games = 0, num_teams = 0;

	all_games = ReadGames(&num_games);
	PrintGames(all_games, num_games);

	table = FillTable(&num_teams, all_games, num_games);
	PrintTable(table, num_teams);

	/*
	FreeAllGames(all_games, num_games);
	FreeAllTeams(table, num_teams);
	*/
}

GAME* ReadGames(int *pngames)
{
	GAME* games = NULL; // NULL is for the realloc()
	GAME game;
	char choice;

	printf("Would you like to add a game? (y/n): ");
	scanf(" %c", &choice);
	while (choice == 'y')
	{
		games = (GAME*)realloc(games, sizeof(GAME) * (*pngames + 1));
		game = ReadGame();
		games[*pngames] = game;
		(*pngames)++;
		printf("Would you like to add a game? (y/n): ");
		scanf(" %c", &choice);
	}

	return games;
}

GAME ReadGame()
{
	GAME game;

	printf("Please enter the name of the first (home) team: ");
	gets(game.name1); // for clearing the buffer
	gets(game.name1);
	printf("Please enter the name of the second (away) team: ");
	gets(game.name2);
	printf("Please enter the number of goals of the first (home) team: ");
	scanf("%d", &game.goals1);
	printf("Please enter the number of goals of the first (away) team: ");
	scanf("%d", &game.goals2);

	return game;
}

// helper function
void PrintGames(GAME games[], int* pngames)
{
	int i;
	for (i = 0; i < pngames; i++)
	{
		printf("\nTeam1 Name: %s - goals: %d\n", games[i].name1, games[i].goals1);
		printf("Team2 Name: %s - goals: %d\n", games[i].name2, games[i].goals2);
	}
	printf("\n");
}

TEAM* FillTable(int *pnum_teams, GAME all_games[], int num_games)
{
	TEAM* table;
	int tsize = 0;

	table = PrepareTable(&tsize, all_games, num_games);
	*pnum_teams = tsize;

	return table;

}

TEAM* PrepareTable(int* tsize, GAME all_games[], int num_games)
{
	TEAM* table = NULL;
	char** names = NULL; // dynamic array of names.
	int num_names = 0;
	int name_length;
	int flag;

	// this part creates a dynamic array of different names that appear in the games.
	int i, j;
	for (i = 0; i < num_games; i++)
	{
		// checks the name of team1
		flag = 1;
		for (j = 0; j < num_names; j++)
		{
			if (strcmp(names[j], all_games[i].name1) == 0) // use of strcmp() to check if the name already exists in the array
				flag = 0;
		}
		if (flag)
		{
			names = (char**)realloc(names, sizeof(char*) * (num_names + 1)); // memory realocation of the names array
			name_length = strlen(all_games[i].name1) + 1;
			names[num_names] = (char*)malloc(sizeof(name_length)); // memory allocation for the name itself
			strcpy(names[num_names], all_games[i].name1);
			num_names++;
		}

		// checks the name of team2
		flag = 1;
		for (j = 0; j < num_names; j++)
		{
			if (strcmp(names[j], all_games[i].name2) == 0) // use of strcmp() to check if the name already exists in the array
				flag = 0;
		}
		if (flag)
		{
			names = (char**)realloc(names, sizeof(char*) * (num_names + 1)); // memory realocation of the names array
			name_length = strlen(all_games[i].name2) + 1;
			names[num_names] = (char*)malloc(sizeof(name_length)); // memory allocation for the name itself
			strcpy(names[num_names], all_games[i].name2);
			num_names++;
		}
	}

	// helper function to print the different found names
	PrintNamesArray(names, num_names);

	for (i = 0; i < num_names; i++) // table initiation
	{
		table = (TEAM*)realloc(table, sizeof(TEAM) * (*tsize + 1));
		strcpy(table[*tsize].name, names[i]);
		table[*tsize].wins = 0;
		table[*tsize].draws = 0;
		table[*tsize].losses = 0;
		table[*tsize].games_played = table[*tsize].wins + table[*tsize].draws + table[*tsize].losses;

		(*tsize)++;
	}

	return table;
}

PrintNamesArray(char** names, int num_names) // helper function
{
	int i;
	for (i = 0; i < num_names; i++)
	{
		puts(names[i]);
	}
	printf("\nThe nuber of names is: %d\n", num_names);
}

void PrintTable(TEAM* table, int num_teams)
{
	printf("Team\t\t\tGP\tW\tD\tL\tList of games played\n\n");

	int i;
	for (i = 0; i < num_teams; i++)
	{
		printf(table[i].name);
		printf("\b\t\t\t%d", table[i].games_played);
		printf("\t%d", table[i].wins);
		printf("\t%d", table[i].draws);
		printf("\t%d\n", table[i].losses);
	}
}









































/*
void tmpFunc()
{

	GAME_NODE* head = NULL;
	GAME_NODE* tail = NULL;
	GAME inputGame;

	if (head == NULL)
	{
		head = (GAME_NODE*)malloc(sizeof(GAME_NODE));
		(*head).agame = inputGame;
		head->next = NULL;
		tail = head;
	}
	else
	{
		tail->next = (GAME_NODE*)malloc(sizeof(GAME_NODE));
		tail = tail->next;
		(*tail).agame = inputGame;
		tail->next = NULL;
	}
}
*/