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
	int loses;
	GAME_NODE* games;
} TEAM;

// Prototypes
GAME* ReadGames(int *pngames);
GAME ReadGame();
void PrintGames(GAME games[], int* pngames); // helper function

TEAM* FillTable(int *pnum_teams, GAME all_games[], int num_games);
TEAM* PrepareTable(int* tsize, GAME all_games[], int num_games);

// Main
void main()
{
	GAME* all_games = NULL;
	TEAM* table = NULL;
	int num_games = 0, num_teams = 0;

	all_games = ReadGames(&num_games);
	PrintGames(all_games, num_games);

	/*
	table = FillTable(&num_teams, all_games, num_games);

	PrintTable(table, num_teams);
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

}

TEAM* PrepareTable(int* tsize, GAME all_games[], int num_games)
{
	TEAM* table;
	char** names = NULL;
	int num_names = 0;

	int i, j;
	for (i = 0; i < num_games; i++)
	{
		
		for (j = 0; j < num_names; j++)
			if (strcmp(names[j], all_games[i].name1) != 0)
			{
				names = (char*)realloc(names, sizeof(char*) * (num_names + 1));
			}
		all_games[i].name1
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