#ifndef HEADER_INCLUDED_EVENT
#define HEADER_INCLUDED_EVENT

#include "struct.h"

int messageBox(char* title, char *message);
void inputInit(leInput* INPUT);
void inputReturn(leInput *INPUT);
void windowInterraction(leInput *INPUT, leState *STATE, SDL_Window *window, leMap *MAP);
void tileEditInterraction(leInput *INPUT, leState *STATE, leMap *MAP);
void layerInterraction(leInput *INPUT, leState *STATE);
void menuInterraction(leInput *INPUT, leState *STATE, leMap *MAP, SDL_Window *window);
void caseReturn(leInput *INPUT, int *x, int *y);
void LOGICAL(leCore *CORE);

#endif
