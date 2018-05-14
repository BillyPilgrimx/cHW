// HW1: SimCity
// Name: Vadim Kobrinsky
// ID: 314257551
// Teacher: Victor
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// Size constants 
#define ROWS 30
#define COLUMNS 55
#define MAX_ROADS 8
#define ROAD_INDICES 4

// Design constants
#define DIRT 177
#define HROAD 45
#define VROAD 124
#define CROAD 32

// Prototypes
void CreateWorld(char** ppWorldMat, int rows, int columns);
void PrintWorld(char** ppWorldMat, int rows, int columns);
int GatherRoadInput(int** ppRoadsMat, int maxNumberOfRoads, int indicesOfRoad, int worldsHorizontalSize, int worldsVerticalSize);
void PrintIndicesMatrix(int** ppRoadsMat, int maxNumberOfRoads, int indicesOfRoad);
void BuildRoads(char** ppWorldMat, int rows, int columns, int** ppRoadsMat, int numOfRoadsToBuild, int indicesOfRoad);

// Main
void main(void) {

	char myWorld[ROWS][COLUMNS];					// gives address to the 2D array and defines its size
	int myRoads[MAX_ROADS][ROAD_INDICES] = { 0 };	// creates a MAX_ROADS * 4 matrix for road points
	int numberOfRoadsToBuild;						// will contain the number of roads to build, given by BuildRoads(...)

	CreateWorld(myWorld, ROWS, COLUMNS);			//	initializes the world with dirt			

	numberOfRoadsToBuild = GatherRoadInput(myRoads, MAX_ROADS, ROAD_INDICES, ROWS, COLUMNS);// gathers the input from the user

	BuildRoads(myWorld, ROWS, COLUMNS, myRoads, numberOfRoadsToBuild, ROAD_INDICES);		// add roads to the dirt world

	PrintWorld(myWorld, ROWS, COLUMNS);														// displays world on screen
}

// initializes the whole world matrix with dirt
void CreateWorld(char** ppWorldMat, int rows, int columns)
{
	char* p = (char*)ppWorldMat; // "flattening" of the world matrix
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			p[i * columns + j] = DIRT;
		}
	}
}

// prints the world matrix
void PrintWorld(char** ppWorldMat, int rows, int columns)
{
	char* p = (char*)ppWorldMat; // "flattening" of the world matrix	
	int i, j;

	printf("This is the world:\n");
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			printf("%c", p[i * columns + j]);
		}
		printf("\n");
	}
	printf("\n");
}

// collects road input from the user, not allowing the user to give incorrect input/stepping out of world's bounds
int GatherRoadInput(int** ppRoadsMat, int maxNumberOfRoads, int indicesOfRoad, int worldsHorizontalSize, int worldsVerticalSize)
{
	int* p = (int*)ppRoadsMat;	// "flattening" of the roads matrix
	int x1, y1, x2, y2;

	int m = 0; // m is the number of roads that eventually are going to be returned
	int n;

	char tmpFlag;
	char flag = 'y';
	while (flag == 'y' && m < maxNumberOfRoads) // forces the user to either choose 'n' (no) or reach maxNumberOfRoads
	{
		n = 0;

		do { // does not allow the first input point to be out of world's bounds
			printf("Enter indices <i,j> of road start: ");
			scanf("%d %d", &x1, &y1);
			if (x1 < 0 || worldsHorizontalSize - 1 < x1 || y1 < 0 || worldsVerticalSize - 1 < y1)
			{
				if (x1 < 0 || worldsHorizontalSize - 1 < x1 || y1 < 0 || worldsVerticalSize - 1 < y1)
					printf("Your input is out of myWorld's bounds! World size: %d x %d. try again...\n", worldsHorizontalSize, worldsVerticalSize);
			}
		} while (x1 < 0 || worldsHorizontalSize - 1 < x1 || y1 < 0 || worldsVerticalSize - 1 < y1);

		do { // does not allow the second input point to be out of world's bounds
			printf("Enter indices <i,j> of road end: ");
			scanf("%d %d", &x2, &y2);
			if (x2 < 0 || worldsHorizontalSize - 1 < x2 || y2 < 0 || worldsVerticalSize - 1 < y2)
			{
				printf("Your input is out of myWorld's bounds! World size: %d x %d. try again...\n", worldsHorizontalSize, worldsVerticalSize);
			}
		} while (x2 < 0 || worldsHorizontalSize - 1 < x2 || y2 < 0 || worldsVerticalSize - 1 < y2);

		// the point matrix will be updated only if the road is horizontal or vertical and has size
		if ((x1 - x2 == 0 || y1 - y2 == 0) && !(x1 == x2 && y1 == y2))
		{
			p[m * indicesOfRoad + n] = x1;
			p[m * indicesOfRoad + (n + 1)] = y1;
			p[m * indicesOfRoad + (n + 2)] = x2;
			p[m * indicesOfRoad + (n + 3)] = y2;
			m++; // moves the counter for the next road
		}
		else
		{
			if ((x1 == x2 && y1 == y2)) // message displayed when same input for road start and road end was received
			{
				printf("Invalid input - roads must have length greater than 0!\n");
			}
			else // message displayed when diagonal road input was received
			{
				printf("Invalid input - roads must be only vertical or horizontal!\n");
			}
		}

		printf("Do you want to enter another road <y/n>? ");
		scanf(" %c", &tmpFlag);
		while (tmpFlag != 'y' && tmpFlag != 'n') // handling invalid input - only 'y' and 'n' allowed!
		{
			printf("Invalid input - answer must be 'y' or 'n' character, try again...\nDo you want to enter another road <y/n>? ");
			scanf(" %c", &tmpFlag);
		}
		flag = tmpFlag;
	}

	if (m == maxNumberOfRoads) // message displayed when maximum number of road has benn reached
	{
		printf("You have reached the maximum amount of roads allowed!\n");
	}

	return m; // returns the number of roads the user wants to build
}

// prints the roads (indices/points) matrix - used for developing this program
void PrintIndicesMatrix(int** ppRoadsMat, int maxNumberOfRoads, int indicesOfRoad)
{
	int* p = (int*)ppRoadsMat; // "flattening" of the roads matrix
	int m, n;

	printf("This is the indices matrix:\n");
	for (m = 0; m < maxNumberOfRoads; m++)
	{
		for (n = 0; n < indicesOfRoad; n++)
		{
			printf("%4d", p[m * indicesOfRoad + n]);
		}
		printf("\n");
	}
	printf("\n");
}

// adds roads which received from the road (indices/points) matrix to the world matrix
void BuildRoads(char** ppWorldMat, int rows, int columns, int** ppRoadsMat, int numOfRoadsToBuild, int indicesOfRoad)
{
	char* wp = (char*)ppWorldMat;	// "flattening" of the world matrix
	int* rp = (int*)ppRoadsMat;		// "flattening" of the roads matrix
	int x1, y1, x2, y2, tmp, length;
	int m, n;

	for (m = 0; m < numOfRoadsToBuild; m++) // extracting road start and end points for easy use and manipulation
	{
		x1 = rp[m * indicesOfRoad];
		y1 = rp[m * indicesOfRoad + 1];
		x2 = rp[m * indicesOfRoad + 2];
		y2 = rp[m * indicesOfRoad + 3];

		if (x1 == x2) // the case of building a horizontal road
		{
			if (y1 > y2) // in case the first input was horizontally larger then the second
			{
				tmp = y2;
				y2 = y1;
				y1 = tmp;
			}

			for (n = y1; n <= y2; n++) // adds a crossroad in case the road is build on a vertical road or crossroad
			{
				if (wp[x1 * columns + n] == VROAD || wp[x1 * columns + n] == CROAD)
				{
					wp[x1 * columns + n] = CROAD;
				}
				else // adds a horizontal road in case the road is build on dirt 
				{
					wp[x1 * columns + n] = HROAD;
				}
			}

		}
		else // y1 == y2 - case of building a vertical road
		{
			if (x1 > x2) // in case the first input was vertically larger then the second
			{
				tmp = x2;
				x2 = x1;
				x1 = tmp;
			}

			length = x2 - x1; // length var for loop limit
			for (n = 0; n <= length; n++) // adds a crossroad in case the road is build on a horizontal road or crossroad
			{
				if (wp[(x1 * columns + y1) + n * columns] == HROAD || wp[(x1 * columns + y1) + n * columns] == CROAD)
				{
					wp[(x1 * columns + y1) + n * columns] = CROAD;
				}
				else // adds a vertical road in case the road is build on dirt 
				{
					wp[(x1 * columns + y1) + n * columns] = VROAD;
				}
			}
		}
	}

	/* a feature that in the last part of this function sweeps the whole matrix
	and connects adjacent, perpendicular roads into crossroads */

	for (m = 0; m < rows * columns; m++)	// runs throught the whole world matrix  
	{
		// for a horizontal road, ckecks and if necessary - updates the relevant surrounding point to a crossroad 
		if (wp[m] == HROAD)
		{
			if (wp[m - 1] == VROAD)
			{
				wp[m - 1] = CROAD;
			}
			else if (wp[m + 1] == VROAD)
			{
				wp[m + 1] = CROAD;
			}
			else if (wp[m - columns] == VROAD)
			{
				wp[m - columns] = CROAD;
			}
			else if (wp[m + columns] == VROAD)
			{
				wp[m + columns] = CROAD;
			}
		}
		// for a vertical road, ckecks and if necessary - updates the relevant surrounding point to a crossroad 
		if (wp[m] == VROAD)
		{
			if (wp[m - 1] == HROAD)
			{
				wp[m - 1] = CROAD;
			}
			else if (wp[m + 1] == HROAD)
			{
				wp[m + 1] = CROAD;
			}
			else if (wp[m - columns] == HROAD)
			{
				wp[m - columns] = CROAD;
			}
			else if (wp[m + columns] == HROAD)
			{
				wp[m + columns] = CROAD;
			}
		}
	}
}

