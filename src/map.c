#include "hdr/struct.h"
#include "hdr/map.h"
#include <stdlib.h>
#include <stdio.h>

#define TINYFILES_IMPL
#include "hdr/tinyfiles.h"

void map_load(leMap *MAP)
{
	tfDIR dir;
	tfDirOpen(&dir, "map");
	tfFILE *allFiles = malloc(0);
	int i = 0, j = 0;

	tfDirNext(&dir); tfDirNext(&dir);

	while (dir.has_next)
	{
		allFiles = realloc(allFiles, (i + 1) * sizeof(tfFILE));
		tfFILE file;
		tfReadFile(&dir, &file);
		tfDirNext(&dir);
		allFiles[i] = file;
		i++;
	}

	int r = rand() % (i);
	printf("Fichier choisi : %d", r + 1);
	tfDirClose(&dir);
	FILE* fichier = NULL;
	fichier = fopen(allFiles[r].path, "r");

	if (fichier != NULL)
	{
		int charactuel = 0;

		// tile1
		do
		{
			charactuel = fgetc(fichier);
		} while (charactuel != '\n');

		for (i = 0; i < HCASE; i++)
			for (j = 0; j < WCASE; j++)
				fscanf(fichier, "%d,", &MAP->tile[i][j]);

		// tile2
		fgetc(fichier);
		do
		{
			charactuel = fgetc(fichier);
		} while (charactuel != '\n');
		for (i = 0; i < HCASE; i++)
			for (j = 0; j < WCASE; j++)
				fscanf(fichier, "%d,", &MAP->tile2[i][j]);

		// obj
		fgetc(fichier);
		do
		{
			charactuel = fgetc(fichier);
		} while (charactuel != '\n');
		for (i = 0; i < HCASE; i++)
			for (j = 0; j < WCASE; j++)
				fscanf(fichier, "%d,", &MAP->obj[i][j]);

		// col
		fgetc(fichier);
		do
		{
			charactuel = fgetc(fichier);
		} while (charactuel != '\n');
		for (i = 0; i < HCASE; i++)
			for (j = 0; j < WCASE; j++)
				fscanf(fichier, "%d,", &MAP->col[i][j]);

		// spawn
		fgetc(fichier);
		fscanf(fichier, "#S#%d,%d", &MAP->sx, &MAP->sy);

		// exit
		fgetc(fichier);
		fscanf(fichier, "#E#%d,%d", &MAP->ex, &MAP->ey);
		printf("ex = %d / ey = %d", MAP->ex, MAP->ey);

		fclose(fichier);
	}

	free(allFiles);
}
