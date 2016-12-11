#include <stdlib.h>

int aleatoire(int min, int max)
{
    const double coeff = rand() / ((double)RAND_MAX);
    return (int)(coeff * (max - min +1) + min);
}
