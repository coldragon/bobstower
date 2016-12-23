#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

int aleatoire(int min, int max)
{
    return (int)(rand()/((double)RAND_MAX)*(max-min+1)+min);
}

int distancepoint(int x1, int y1, int x2, int y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

int collisioncercle(SDL_Rect p1, int d1, SDL_Rect p2, int d2)
{
    if (distancepoint(p1.x, p1.y, p2.x, p2.y)<d1+d2)
        return 1;
    else
        return 0;
}

int collisionrect(SDL_Rect rect1, SDL_Rect rect2)
{
    if (rect1.x < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x && rect1.y < rect2.y + rect2.h && rect1.h + rect1.y > rect2.y)
        return 1;
    else
        return 0;
}
