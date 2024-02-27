#include "Random.hpp"
#include <stdlib.h>
#include <time.h>
using namespace std;

double equiproba(int previous, int next, double(*g)(double)){
    srand48(time(NULL));
    double w = drand48();
    if (g(-1) == 0){
        w *= 6./(next+previous);
    }else{
        w -= 0.5;
        w *= 12./(previous+next);
    }
    return w;
}