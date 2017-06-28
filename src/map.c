#include "hdr/struct.h"
#include "hdr/map.h"
#include <stdlib.h>
#include <stdio.h>

#if defined( _WIN32 )
#include <Windows.h>
#endif

#include <TINYHEADERS/tinyfiles.h>

void next_map_load()
{
tfDIR dir;
tfDirOpen(&dir, "map");
tfFILE *allFiles = malloc(0);
int i = 0;

#if defined( _WIN32 )
	tfDirNext(&dir); tfDirNext(&dir);
#endif

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
tfDirClose(&dir);
FILE* fichier = NULL;
//char path[500] = "map\\";
//strcat(path, allFiles[r].name);
fichier = fopen(allFiles[r].path, "r");
if (fichier != NULL)
{
	int charactuel = 0;
	do
	{
		charactuel = fgetc(fichier);
		printf("%c", charactuel);
	} while (charactuel != EOF);

	fclose(fichier);
}
free(allFiles);
}
