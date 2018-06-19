#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <Windows.h>

// size definitions
#define HEIGHT 800
#define WIDTH 1000
#define R_WIDTH 20
#define CR_RADIUS 15

// files definitions
#define IN_FNAME "input.txt"
#define OUT_FNAME "output.txt"

// *** color definition ***
// background - Emerald (green)
#define BG_R 20
#define BG_G 220
#define BG_B 100
// residential house - Watermelon (pink)
#define RES_HOUSE_R 254
#define RES_HOUSE_G	127
#define RES_HOUSE_B	156
// commercial house - Olympic (blue)
#define COM_HOUSE_R 0
#define COM_HOUSE_G 142
#define COM_HOUSE_B 204
// industrial house - Royal (yellow)
#define IND_HOUSE_R 250
#define IND_HOUSE_R 218
#define IND_HOUSE_R 94
//  road - Light Grey
#define ROAD_R 202
#define ROAD_G 204
#define ROAD_B 206
// crossroad - Imperial Red
#define CROSSROAD_R 237
#define CROSSROAD_G 41
#define CROSSROAD_B 57

// type definitions
typedef struct color
{
	int red, green, blue;
} COLOR;

typedef struct house
{
	int cx, cy;			// central x & y coordinates
	int height, width;	
	int houseType;		// 1 = residential, 2 = commercial, 3 = industrial
	COLOR color;

} HOUSE;

typedef struct house_node
{
	HOUSE aHouse;
	struct house_node* next;

} HOUSE_NODE;

typedef struct road
{
	int x1, y1, x2, y2;
	COLOR color;

} ROAD;

typedef struct road_node
{
	ROAD aRoad;
	struct road_node* next;

} ROAD_NODE;

typedef struct crossroad
{
	ROAD roadA, roadB;
	COLOR color;

} CROSSROADS;

typedef struct crossroad_node
{
	CROSSROADS aCrossRoad;
	struct crossroad* next;

} CROSSROAD_NODE;

// prototypes


// main
void main()
{
	HOUSE_NODE* houses = NULL;		   // dynamic array of houses
	ROAD_NODE* roads = NULL;		   // dynamic array of roads
	CROSSROAD_NODE* crossroads = NULL; // dynamic array of crossroads
	int num_houses;
	int num_roads;
	int num_crossroads;

	FILE* pf = fopen(IN_FNAME, "r");
	if (pf == NULL) // in case the file cannot be found
	{
		printf("Can't open the file %s...\n", IN_FNAME);
		exit(1);	// emergency exit
	}

	houses = ReadHouses(pf, num_houses);
	roads = ReadRoads(pf, num_roads);
	crossroads = CreateCrossRoads(roads, num_roads, num_crossroads);



	fclose(pf);
	WriteBitmap(OUT_FNAME, houses, num_houses, roads, num_roads, crossroads, num_crossroads);
	printf("Done!\n");
}

void WriteBitmap(char* out_fname, HOUSE_NODE* houses, int num_houses, ROAD_NODE* roads, int num_roads, CROSSROAD_NODE* crossroads, int num_crossroads)
{
	FILE* pf = fopen(out_fname, "wb");
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	unsigned char* bmp;
	int i, j, size;
	
	size = HEIGHT * WIDTH * 3;
	bmp = (unsigned char*)malloc(size * sizeof(unsigned char));
	// defining file header
	bf.bfType = 0x4d42;
	bf.bfSize = size + sizeof(bf) + sizeof(bi);
	bf.bfOffBits = sizeof(bf) + sizeof(bi);
	// defining info header
	bi.biHeight = HEIGHT;
	bi.biWidth = WIDTH;
	bi.biSize = sizeof(bi);
	bi.biBitCount = 24;
	bi.biCompression = BI_RGB;
	// defining the bmp - the background in Emerald color
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			bmp[(i * WIDTH + j) * 3 + 0] = BG_R; // the red part of the background
			bmp[(i * WIDTH + j) * 3 + 1] = BG_G; // the green part of the background
			bmp[(i * WIDTH + j) * 3 + 2] = BG_B; // the blue part of the background
		}
	}

	// adding houses, roads and crossroads
	for (i = 0; i < num_houses; i++)
	{
		AddHouse(bmp, houses[i]);
	}

	for (i = 0; i < num_roads; i++)
	{
		AddRoad(bmp, roads[i]);
	}

	for (i = 0; i < num_crossroads; i++)
	{
		AddCrossroad(bmp, crossroads[i]);
	}

	// saving the data
	fwrite(&bf, sizeof(bf), 1, pf);
	fwrite(&bi, sizeof(bf), 1, pf);
	fwrite(bmp, 1, size, pf);
	
	fclose(pf);
	free(bmp);
}



