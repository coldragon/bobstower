#ifndef HEADER_INCLUDED_BASIC
#define HEADER_INCLUDED_BASIC

int aleatoire(int min, int max);
int distancepoint(int x1, int y1, int x2, int y2);
int collisioncercle(SDL_Rect p1, int d1, SDL_Rect p2, int d2);
int collisionrect(SDL_Rect rect1, SDL_Rect rect2);

#endif
