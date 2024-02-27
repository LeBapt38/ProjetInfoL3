#include "Random.hpp"
#include <stdlib.h>
#include <time.h>
using namespace std;

double equiproba(int previous, int next, double(*g)(double)){
    srand(time(NULL));
    double w = rand()/(1.*0x7fffffff);
    if (g(-1) == 0){
        w *= 6./(next+previous);
    }else{
        w -= 0.5;
        w *= 12./(previous+next);
    }
    return w;
}