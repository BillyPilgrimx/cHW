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
void PrintGames(GAME games[], int pngames); // helper function
TEAM* FillTable(int *pnum_teams, GAME all_games[], int num_games);
TEAM* PrepareTable(int* tsize, GAME all_games[], int num_games);
void PrintTable(TEAM* table, int num_teams);
void UpdateListOfGames(GAME_NODE* head, GAME* game); // helper function
GAME_NODE* FindTail(GAME_NODE* head); // helper function
void PrintLinkedList(GAME_NODE* head); // helper function
void FreeAllGames(GAME all_games[], int num_games);
void FreeAllTeams(TEAM* table, int num_teams);

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

	FreeAllGames(all_games, num_games);
	FreeAllTeams(table, num_teams);
}

GAME* ReadGames(int *pngames) // a function that manages the whole user input.
{
	GAME* games = NULL; // NULL is for the realloc()
	GAME game;
	char choice;
	int flag = 1;

	printf("Would you like to add a game? (y/n): ");
	scanf(" %c", &choice);

	while (flag == 1) // incase of invalid input
	{
		flag = 0;
		if (choice == 'y')
		{
			flag = 1;
			games = (GAME*)realloc(games, sizeof(GAME) * (*pngames + 1));
			game = ReadGame();
			games[*pngames] = game;
			(*pngames)++;
			printf("Would you like to add a game? (y/n): ");
			scanf(" %c", &choice);
		}
		else if (choice != 'y' && choice != 'n')
		{
			flag = 1;
			printf("Invalid input, try again...\n");
			printf("Would you like to add a game? (y/n): ");
			scanf(" %c", &choice);
		}
	}

	return games;
}

GAME ReadGame() // a function that manages the input of a single game.
{
	GAME game;

	printf("Please enter the name of the 1st (home) team: ");
	gets(game.name1); // for clearing the buffer
	gets(game.name1);
	printf("Please enter the name of the 2nd (away) team: ");
	gets(game.name2);
	printf("Please enter the number of goals of the 1st (home) team: ");
	scanf("%d", &game.goals1);
	printf("Please enter the number of goals of the 2nd (away) team: ");
	scanf("%d", &game.goals2);

	return game;
}

void PrintGames(GAME games[], int pngames) // a helper func that displayes all the games.
{
	if (pngames == 0)
	{
		printf("\nThere are no games played!\n\n");
		return;
	}

	printf("\nThese are all the games played:\n");
	int i;
	for (i = 0; i < pngames; i++)
	{
		printf("\n%s  %d : %d  %s\n", games[i].name1, games[i].goals1, games[i].goals2, games[i].name2);
	}
	printf("\n\n");
}

TEAM* FillTable(int *pnum_teams, GAME all_games[], int num_games) // a wraper function that executes PrepareTable() and updates
{																  // the number of all teams.
	TEAM* table;
	int tsize = 0;

	table = PrepareTable(&tsize, all_games, num_games);
	*pnum_teams = tsize;

	return table;
}

TEAM* PrepareTable(int* tsize, GAME all_games[], int num_games) // a function that manages the whole table.
{

	GAME_NODE* games = NULL;
	GAME_NODE* tail = NULL;
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
			names[num_names] = (char*)malloc(sizeof(char) * name_length); // memory allocation for the name itself
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
			names[num_names] = (char*)malloc(sizeof(char) * name_length); // memory allocation for the name itself
			strcpy(names[num_names], all_games[i].name2);
			num_names++;
		}
	}

	for (i = 0; i < num_names; i++) // table initiation with names and zero values and .games as NULL
	{
		table = (TEAM*)realloc(table, sizeof(TEAM) * (*tsize + 1));
		strcpy(table[*tsize].name, names[i]);
		table[*tsize].wins = 0;
		table[*tsize].draws = 0;
		table[*tsize].losses = 0;
		table[*tsize].games_played = table[*tsize].wins + table[*tsize].draws + table[*tsize].losses;
		table[*tsize].games = (GAME_NODE*)malloc(sizeof(GAME_NODE));
		table[*tsize].games = NULL; // NULL means no games played yet
		(*tsize)++;
	}

	for (i = 0; i < num_games; i++)
	{
		if (all_games[i].goals1 < all_games[i].goals2) // in case the score is A < B
		{
			for (j = 0; j < *tsize; j++)
			{
				if (strcmp(table[j].name, all_games[i].name1) == 0)
				{
					table[j].losses++;
					table[j].games_played = table[j].wins + table[j].draws + table[j].losses;
					if (table[j].games == NULL) // in case this is the first game of team A
					{
						table[j].games = (GAME_NODE*)malloc(sizeof(GAME_NODE));
						table[j].games->agame = all_games[i];
						table[j].games->next = NULL;
					}
					else // not a first game
						UpdateListOfGames(table[j].games, &all_games[i]);
				}
				if (strcmp(table[j].name, all_games[i].name2) == 0)
				{
					table[j].wins++;
					table[j].games_played = table[j].wins + table[j].draws + table[j].losses;
					if (table[j].games == NULL) // in case this is the first game of team B
					{
						table[j].games = (GAME_NODE*)malloc(sizeof(GAME_NODE));
						table[j].games->agame = all_games[i];
						table[j].games->next = NULL;
					}
					else // not a first game
						UpdateListOfGames(table[j].games, &all_games[i]);
				}
			}
		}

		else if (all_games[i].goals1 == all_games[i].goals2) // in case the score is A = B
		{
			for (j = 0; j < *tsize; j++)
			{
				if (strcmp(table[j].name, all_games[i].name1) == 0)
				{
					table[j].draws++;
					table[j].games_played = table[j].wins + table[j].draws + table[j].losses;
					if (table[j].games == NULL) // in case this is the first game of team A
					{
						table[j].games = (GAME_NODE*)malloc(sizeof(GAME_NODE));
						table[j].games->agame = all_games[i];
						table[j].games->next = NULL;
					}
					else // not a first game
						UpdateListOfGames(table[j].games, &all_games[i]);
				}


				if (strcmp(table[j].name, all_games[i].name2) == 0)
				{
					table[j].draws++;
					table[j].games_played = table[j].wins + table[j].draws + table[j].losses;
					if (table[j].games == NULL) // in case this is the first game of team B
					{
						table[j].games = (GAME_NODE*)malloc(sizeof(GAME_NODE));
						table[j].games->agame = all_games[i];
						table[j].games->next = NULL;
					}
					else // not a first game
						UpdateListOfGames(table[j].games, &all_games[i]);
				}
			}
		}
		else // in case the score is A > B
		{
			for (j = 0; j < *tsize; j++)
			{
				if (strcmp(table[j].name, all_games[i].name1) == 0)
				{
					table[j].wins++;
					table[j].games_played = table[j].wins + table[j].draws + table[j].losses;
					if (table[j].games == NULL) // in case this is the first game of team A
					{
						table[j].games = (GAME_NODE*)malloc(sizeof(GAME_NODE));
						table[j].games->agame = all_games[i];
						table[j].games->next = NULL;
					}
					else // not a first game
						UpdateListOfGames(table[j].games, &all_games[i]);
				}
				if (strcmp(table[j].name, all_games[i].name2) == 0)
				{
					table[j].losses++;
					table[j].games_played = table[j].wins + table[j].draws + table[j].losses;
					if (table[j].games == NULL) // in case this is the first game of team B
					{
						table[j].games = (GAME_NODE*)malloc(sizeof(GAME_NODE));
						table[j].games->agame = all_games[i];
						table[j].games->next = NULL;
					}
					else // not a first game
						UpdateListOfGames(table[j].games, &all_games[i]);
				}
			}
		}
	}

	return table;
}

void PrintTable(TEAM* table, int num_teams) // prints the table.
{
	printf("Team\t\t\tGP\tW\tD\tL\tList of games played\n\n");
	int i;
	for (i = 0; i < num_teams; i++)
	{
		printf(table[i].name);
		printf("\t\t\t%d", table[i].games_played);
		printf("\t%d", table[i].wins);
		printf("\t%d", table[i].draws);
		printf("\t%d\t", table[i].losses);
		PrintLinkedList(table[i].games);
	}
}

void UpdateListOfGames(GAME_NODE* head, GAME* game) // a helper function that manages the linked list of games.
{
	
	if (head->next == NULL)
	{
		GAME_NODE* tmpTail = NULL;
		tmpTail = FindTail(head);
		tmpTail = tmpTail->next;
		tmpTail = (GAME_NODE*)malloc(sizeof(GAME_NODE));
		head->next = tmpTail;
		tmpTail->agame = *game;
		tmpTail->next = NULL;
	}
	else
	{
		UpdateListOfGames(head->next, game);
	}
}

GAME_NODE* FindTail(GAME_NODE* head) // a recursive help func to find the last element in the linked list (used in UpdateListOfGames()).
{
	if (head->next == NULL)
	{
		return head;
	}
	else
	{
		return FindTail(head->next);
	}
}

void PrintLinkedList(GAME_NODE* head) // prints the 'List of games played' in the table, used in PrintTable().
{
	if (head->next == NULL)
	{
		printf("{%s %d : %d %s} -> NULL\n", head->agame.name1, head->agame.goals1, head->agame.goals2, head->agame.name2);
	}
	else
	{
		printf("{%s %d : %d %s} -> ", head->agame.name1, head->agame.goals1, head->agame.goals2, head->agame.name2);
		PrintLinkedList(head->next);
	}
}

void FreeAllGames(GAME all_games[], int num_games) // the names are static array, to create all_games I used realloc() 
{												   // so there is only all_games[] to set free...									
	if (num_games > 0)
	{
		free(all_games);
		printf("\nAll games have been freed.");
	}
}

void FreeAllTeams(TEAM* table, int num_teams) // frees all GAME_NODEs as well the whole table in the end. 
{
	if (num_teams > 0)
	{
		GAME_NODE* head = NULL;
		GAME_NODE* tmpHead = NULL;

		int i;
		for (i = 0; i < num_teams; i++)
		{
			head = ((&table[i])->games);

			while (head->next != NULL)
			{
				tmpHead = head->next;
				free(head);
				head = tmpHead;
			}
			free(head);
		}

		free(table);
		printf("\nAll teams have been freed.\n");
	}
}


