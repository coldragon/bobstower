#ifndef HEADER_INCLUDED_MAP
#define HEADER_INCLUDED_MAP

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "struct.h"

#ifndef WIN32

#include <sys/types.h>

#endif

void next_map_load(leMap MAP);

#endif
