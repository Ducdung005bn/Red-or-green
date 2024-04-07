#include "Light.h"
#include "Common_Function.h"

double RandomNumber() { 
    srand(time(0));
    int randomIndex = rand() % 4;
    double numberArray[] = {1.5, 2, 2.5, 3};
    return numberArray[randomIndex];
}

