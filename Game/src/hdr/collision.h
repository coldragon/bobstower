#ifndef HEADER_INCLUDED_COLLISION
#define HEADER_INCLUDED_COLLISION
#include "struct.h"

int collisionmap(SDL_Rect *rect, leMap *MAP, int type, int haut, int bas, int gauche, int droite);
void collisionEnm(leBob *ENM, leMap *MAP, leBob *BOB);
void objetcollision(leMap *MAP, leBob *BOB, leAudio *JEU);
void sortcollision(leMap *MAP, leBob *ENM, leAudio *JEU, leBob *BOB);

#endif
