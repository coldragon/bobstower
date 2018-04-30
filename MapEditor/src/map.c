#include "hdr/struct.h"
#include "hdr/map.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
	#include <Windows.h>
#endif

void map_init(leMap *MAP)
{
	MAP->quitfloor = 0;
	memset(MAP->tile, 0, sizeof(MAP->tile));
	memset(MAP->tile2, 0, sizeof(MAP->tile2));
	memset(MAP->obj, 0, sizeof(MAP->obj));
	memset(MAP->col, 0, sizeof(MAP->col));
	MAP->ey = 0; MAP->ex = 0;
	MAP->sy = 0; MAP->sx = 0;
}

#if defined (_WIN32) || defined (_WIN64)

INT LoadFile(char* FileName)
{
	OPENFILENAME  ofn;
	memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.hInstance = NULL;
	ofn.lpstrFilter = "Text Files\0*.txt\0\0";
	ofn.lpstrFile = FileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Please Select A File To Open";
	ofn.Flags = OFN_NONETWORKBUTTON |
		OFN_FILEMUSTEXIST |
		OFN_HIDEREADONLY;
	if (!GetOpenFileName(&ofn))
		return(0);
	return 1;
}

INT SaveFile(char* FileName)
{
	OPENFILENAME  ofn;
	memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.hInstance = NULL;
	ofn.lpstrFilter = "Text Files\0*.txt\0\0";
	ofn.lpstrFile = FileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Choose where to save file";
	ofn.Flags = OFN_NONETWORKBUTTON |
		OFN_HIDEREADONLY;
	if (!GetSaveFileName(&ofn))
		return(0);
	return 1;
}

#endif

void map_load(leMap *MAP, char* path)
{
	FILE* fichier = fopen(path, "r"); 
	printf("%s \n", path);
	int i, j;
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
		fscanf(fichier, "#S#%d,%d", &MAP->sy, &MAP->sx);

		// exit
		fgetc(fichier);
		fscanf(fichier, "#E#%d,%d", &MAP->ey, &MAP->ex);
		
		fclose(fichier);
	}
}

void map_save(leMap *MAP, char *path2, int usepath)
{	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	
	char path[300];
	sprintf(path, "save_map/map-%d-%d-%d-%.2dh%.2dm%.2ds.txt",timeinfo->tm_mday,timeinfo->tm_mon,1900+timeinfo->tm_year,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
	int i = 0, j = 0;
	if(usepath)
		strcpy(path, path2);
	FILE* fichier = fopen(path, "w+");
	if (fichier != NULL)
	{
		// tile1
		fprintf(fichier, "#TILE1\n");
		for (i = 0; i < HCASE; i++)
		{
			for (j = 0; j < WCASE; j++)
				fprintf(fichier, "%d,", MAP->tile[i][j]);
			fprintf(fichier, "\n");
		}

		// tile2
		fprintf(fichier, "#TILE2\n");
		for (i = 0; i < HCASE; i++)
		{
			for (j = 0; j < WCASE; j++)
				fprintf(fichier, "%d,", MAP->tile2[i][j]);
			fprintf(fichier, "\n");
		}

		// obj
		fprintf(fichier, "#OBJ\n");
		for (i = 0; i < HCASE; i++)
		{
			for (j = 0; j < WCASE; j++)
				fprintf(fichier, "%d,", MAP->obj[i][j]);
			fprintf(fichier, "\n");
		}

		// col
		fprintf(fichier, "#COL\n");
		for (i = 0; i < HCASE; i++)
		{
			for (j = 0; j < WCASE; j++)
				fprintf(fichier, "%d,", MAP->col[i][j]);
			fprintf(fichier, "\n");
		}

		// spawn
		fprintf(fichier, "#S#%d,%d\n", MAP->sy, MAP->sx);

		// exit
		fprintf(fichier, "#E#%d,%d\n", MAP->ey, MAP->ex);

		fclose(fichier);

		char message[255];
		sprintf(message, "Map saved at : %s ", path);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Saved",message,NULL);
	}
}