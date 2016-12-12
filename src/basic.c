#include <stdlib.h>
#include <math.h>

int aleatoire(int min, int max)
{
    const double coeff = rand() / ((double)RAND_MAX);
    return (int)(coeff * (max - min +1) + min);
}

double distancepoint(int x1, int y1, int x2, int y2)
{
    double distance;
    distance=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    return (int)distance;
}
