#ifndef HEADER_INCLUDED_INIT
#define HEADER_INCLUDED_INIT
#include "struct.h"

void open_sdl_shit();
void close_sdl_shit();
void coreInit(leCore *CORE);
void coreFree(leCore *CORE);
void mainLoop(leCore *CORE);

#endif
