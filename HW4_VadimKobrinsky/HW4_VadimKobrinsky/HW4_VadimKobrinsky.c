#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <Windows.h>

// constants definitions
#define HEIGHT 800
#define WIDTH 1000
#define R_WIDTH 20
#define IN_FNAME "input.txt"
#define OUT_FNAME "output.txt"

// type definitions
typedef struct color
{
	int red, green, blue;
} COLOR;

typedef struct house
{
	int cx, cy;
	int height, width;
	char houseType;
	COLOR color;

} HOUSE;

typedef struct road
{
	int x1, y1, x2, y2;

} ROAD;

typedef struct house_node
{
	HOUSE aHouse;
	struct house_node* next;

} HOUSE_NODE;

typedef struct road_node
{
	ROAD aRoad;
	struct road_node* next;
} ROAD_NODE;

// prototypes


// main
void main()
{
	HOUSE* houseArr; // dynamic array of houses
	ROAD* roadArr; // dynamic array of roads
	int num_houses;
	int num_roads;
	FILE* pf = fopen(IN_FNAME, "r");

	if (pf == NULL)
	{
		printf("Can't open the file %s...\n", IN_FNAME);
		exit(1); // emergency exit
	}

	houseArr = ReadHouses(pf, num_houses);
	roadArr = ReadRoads(pf, num_roads);



	fclose(pf);
	WriteBitmap(OUT_FNAME, )
}