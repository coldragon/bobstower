#ifndef HEADER_INCLUDED_MAP
#define HEADER_INCLUDED_MAP

#include "hdr/struct.h"
#if defined ( _WIN32 ) || defined ( _WIN64 );
	#include "Windows.h"
#endif

void map_init(leMap *MAP);

#if defined ( _WIN32 ) || defined ( _WIN64 );

INT LoadFile(char* FileName);
INT SaveFile(char* FileName);

#endif

void map_load(leMap *MAP, char* path);
void map_save(leMap *MAP, char *path, int usepath);

#endif
