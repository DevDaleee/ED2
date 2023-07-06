#include <stdio.h>
#include <stdlib.h>
#include "arv234.h"

typedef struct Arv23{
    int info1, info2;
    arv23 *left, *center, *dir;
}arv23;

