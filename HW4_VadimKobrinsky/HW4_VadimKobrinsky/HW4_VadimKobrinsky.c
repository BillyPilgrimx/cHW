#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <Windows.h>

// size definitions
#define HEIGHT 800
#define WIDTH 1000
#define HR_WIDTH 20  // half of road width
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
#define IND_HOUSE_G 218
#define IND_HOUSE_B 94
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
void WriteBitmap(char* out_fname, HOUSE_NODE* houses, ROAD_NODE* roads, CROSSROAD_NODE* crossroads);
void AddHouse(unsigned char* bmp, HOUSE_NODE* houses);
void AddRoad(unsigned char* bmp, ROAD_NODE* roads);
void AddCrossroad(unsigned char* bmp, CROSSROAD_NODE* crossroads);

// main
void main()
{
	HOUSE_NODE* houses = NULL;		   // dynamic array of houses
	ROAD_NODE* roads = NULL;		   // dynamic array of roads
	CROSSROAD_NODE* crossroads = NULL; // dynamic array of crossroads

	FILE* pf = fopen(IN_FNAME, "r");
	if (pf == NULL) // in case the file cannot be found
	{
		printf("Can't open the file %s...\n", IN_FNAME);
		exit(1);	// emergency exit
	}

	ReadHouses(pf, houses);
	ReadRoads(pf, roads);
	CreateCrossRoads(roads, crossroads);

	fclose(pf);
	WriteBitmap(OUT_FNAME, houses, roads, crossroads);
	printf("Done!\n");
}

void WriteBitmap(char* out_fname, HOUSE_NODE* houses, ROAD_NODE* roads, CROSSROAD_NODE* crossroads)
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
	AddHouse(bmp, houses);
	AddRoad(bmp, roads);
	AddCrossroad(bmp, crossroads);


	// saving the data
	fwrite(&bf, sizeof(bf), 1, pf);
	fwrite(&bi, sizeof(bf), 1, pf);
	fwrite(bmp, 1, size, pf);

	fclose(pf);
	free(bmp);
}

void AddHouse(unsigned char* bmp, HOUSE_NODE* houses)
{
	int i, j, left, right, bottom, top;

	if (houses == NULL) // in case there are no houses to add
	{
		printf("There are no houses to create...\n");
		return;
	}
	else
	{
		left = (houses->aHouse.cx) - (houses->aHouse.width / 2);
		right = (houses->aHouse.cx) + (houses->aHouse.width / 2);
		bottom = (houses->aHouse.cy) - (houses->aHouse.height / 2);
		top = (houses->aHouse.cy) + (houses->aHouse.height / 2);

		for (i = bottom; i < top; i++)
		{
			for (j = left; j < right; j++)
			{
				switch (houses->aHouse.houseType)
				{
				case 1: // residential house
					bmp[(i * WIDTH + j) * 3 + 0] = RES_HOUSE_R; // red
					bmp[(i * WIDTH + j) * 3 + 1] = RES_HOUSE_G; // green
					bmp[(i * WIDTH + j) * 3 + 2] = RES_HOUSE_B; // blue
					break;
				case 2: // commercial house
					bmp[(i * WIDTH + j) * 3 + 0] = COM_HOUSE_R; // red
					bmp[(i * WIDTH + j) * 3 + 1] = COM_HOUSE_G; // green
					bmp[(i * WIDTH + j) * 3 + 2] = COM_HOUSE_B; // blue
					break;
				case 3: // industrail house
					bmp[(i * WIDTH + j) * 3 + 0] = IND_HOUSE_R; // red
					bmp[(i * WIDTH + j) * 3 + 1] = IND_HOUSE_G; // green
					bmp[(i * WIDTH + j) * 3 + 2] = IND_HOUSE_B; // blue
					break;
				}
			}
		}

		if (houses->next != NULL)
		{
			AddHouse(bmp, houses->next);
		}
	}
}

void AddRoad(unsigned char* bmp, ROAD_NODE* roads)
{
	int i, j, left, right, bottom, top;

	if (roads == NULL) // in case there are no roads to add
	{
		printf("There are no roads to create...\n");
		return;
	}
	else
	{
		if (roads->aRoad.y1 == roads->aRoad.y2) // in case a horizontal road
		{
			left = roads->aRoad.x1;
			right = roads->aRoad.x2;
			bottom = (roads->aRoad.y1 - HR_WIDTH);
			top = (roads->aRoad.y1 + HR_WIDTH);
		}
		else									// in case a vertical road
		{
			left = (roads->aRoad.x1 - HR_WIDTH);
			right = (roads->aRoad.x1 + HR_WIDTH);
			bottom = roads->aRoad.y1;
			top = roads->aRoad.y2;
		}

		for (i = bottom; i < top; i++)
		{
			for (j = left; j < right; j++)
			{
				bmp[(i * WIDTH + j) * 3 + 0] = ROAD_R; // red
				bmp[(i * WIDTH + j) * 3 + 1] = ROAD_G; // green
				bmp[(i * WIDTH + j) * 3 + 2] = ROAD_B; // blue
			}
		}

		if (roads->next != NULL)
		{
			AddHouse(bmp, roads->next);
		}
	}
}

void AddCrossroad(unsigned char* bmp, CROSSROAD_NODE* crossroads)
{
	int i, j, left, right, bottom, top, cx, cy;
	double dist;

	if (crossroads == NULL) // in case there are no crossroads to add
	{
		printf("There are no crossroads to create...\n");
		return;
	}
	else
	{
		if (crossroads->aCrossRoad.roadA.y1 == crossroads->aCrossRoad.roadA.y2) // in case roadA is horizontal (and roadB vertical)
		{
			cx = crossroads->aCrossRoad.roadB.x1;
			cy = crossroads->aCrossRoad.roadA.y1;
		}
		else                                                                    // in case roadA is vertical (and roadB horizontal)
		{
			cx = crossroads->aCrossRoad.roadA.x1;
			cy = crossroads->aCrossRoad.roadB.y1;
		}

		left = cx - CR_RADIUS;
		right = cx + CR_RADIUS;
		bottom = cy - CR_RADIUS;
		top = cy + CR_RADIUS;

		for (i = bottom; i < top; i++)
		{
			for (j = left; j < right; j++)
			{
				dist = sqrt((i - cy) * (i - cy) + (j - cx) * (j - cx));
				if (dist < CR_RADIUS)
				{
					bmp[(i * WIDTH + j) * 3 + 0] = CROSSROAD_R; // red
					bmp[(i * WIDTH + j) * 3 + 1] = CROSSROAD_G; // green
					bmp[(i * WIDTH + j) * 3 + 2] = CROSSROAD_B; // blue
				}
			}
		}

		if (crossroads->next != NULL)
		{
			AddHouse(bmp, crossroads->next);
		}
	}

}

void ReadHouses(FILE* pf, HOUSE_NODE* houses)
{
	char kind;
	int tmp;

	while (!feof(pf))
	{
		fscanf(pf, " %c", &kind);
		if (kind == 'h')
		{
			if (houses == NULL)
			{
				houses = (CROSSROAD_NODE*)realloc(houses, sizeof(CROSSROAD_NODE));
				houses->next = NULL;
				fscanf(pf, "%d%d%d%d%d", houses->aHouse.cx, houses->aHouse.cy, houses->aHouse.height, houses->aHouse.width, houses->aHouse.houseType);
				
			}
			else if (houses->next == NULL)
			{
				houses->next = (CROSSROAD_NODE*)realloc(houses, sizeof(CROSSROAD_NODE));
				houses->next->next = NULL;
				houses->next = houses;

			}

			switch (houses->aHouse.houseType)
			{

			case 1:
				houses->aHouse.color.red = RES_HOUSE_R;
				houses->aHouse.color.green = RES_HOUSE_G;
				houses->aHouse.color.blue = RES_HOUSE_B;
				break;

			case 2:
				houses->aHouse.color.red = COM_HOUSE_R;
				houses->aHouse.color.green = COM_HOUSE_G;
				houses->aHouse.color.blue = COM_HOUSE_B;
				break;

			case 3:
				houses->aHouse.color.red = IND_HOUSE_R;
				houses->aHouse.color.green = IND_HOUSE_G;
				houses->aHouse.color.blue = IND_HOUSE_B;
				break;
			}

			ReadHouses(pf, houses);
		}

	}

}















