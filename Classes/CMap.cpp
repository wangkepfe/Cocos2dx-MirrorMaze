#include "CMap.h"
#include <stdio.h>

void CMap::setMap(int index)
{
	int i, j;

	map = new BlockInfo*[MAP_LENGTH];
	for (i = 0; i < MAP_LENGTH; i++)
	{
		map[i] = new BlockInfo[MAP_HEIGHT];
	}

	FILE * pFile1, *pFile2;

	char fileRoute[17];

	sprintf(fileRoute, "map/map%d.csv", index);
	pFile1 = fopen(fileRoute, "r");

	sprintf(fileRoute, "map/direc%d.csv", index);
	pFile2 = fopen(fileRoute, "r");

	//switch (index)
	//{
	//case 1:	pFile1 = fopen("map/map01.csv", "r");
	//		pFile2 = fopen("map/direc01.csv", "r");
	//		break;
	//case 2:	pFile1 = fopen("map/map02.csv", "r");
	//		pFile2 = fopen("map/direc02.csv", "r");
	//		break;
	//case 11:	pFile1 = fopen("map/map3.csv", "r");
	//		pFile2 = fopen("map/direc3.csv", "r");
	//		break;
	//case 12:	pFile1 = fopen("map/map4.csv", "r");
	//		pFile2 = fopen("map/direc4.csv", "r");
	//		break;
	//default:pFile1 = fopen("map/map1.csv", "r");
	//		pFile2 = fopen("map/direc1.csv", "r");
	//		break;
	//}

	int x, y;
	char c;

	for (j = 0; j < MAP_HEIGHT; j++)
	{
		for (i = 0; i < MAP_LENGTH ; i++)
		{	
			fscanf(pFile1, "%d", &x);
			fscanf(pFile1, "%c", &c);

			fscanf(pFile2, "%d", &y);
			fscanf(pFile2, "%c", &c);

			map[i][j].type = (BlockType)x;
			map[i][j].direc = (BlockDirec)(y - 1);
			map[i][j].state = Nostate;
		}
	}
	fclose(pFile1);
	fclose(pFile2);
/*
	map[5][0].type = Emitter;

	map[5][5].type = OneFaceMirror;

	map[7][5].type = OneFaceMirror;
	map[7][5].direc = up;

	map[7][9].type = OneFaceMirror;*/
}

BlockInfo ** CMap::getMap()
{
	return map;
}
