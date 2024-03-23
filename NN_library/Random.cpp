#include "Random.hpp"
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

double equiproba(int previous, int next, double(*g)(double)){
    srand48(time(NULL));
    double w = drand48();
    // Le premier cas évite de "perdre" trop de coefficient pour une fonction d'activation comme Relu
    if (g(-1) == 0){
        w *= 6./(next+previous);
    }else{
        w -= 0.5;
        w *= 12./(previous+next);
    }
    return w;
}

double normal(int previous, int next, double(*g)(double)){
    srand48(time(NULL));
    double w = 0;
    if (g(-1) == 0){
        do{
            double sig = sqrt(4./(next+previous));
            w = Gaussian(sig);
        }while(w < 0);
    }else{
        double sig = sqrt(2./(next+previous));
        w = Gaussian(sig);
    }
}

double Gaussian(double sig) {
    double u1 = drand48();
    double u2 = drand48();
    // Transformation de Box-Muller pour obtenir une valeur gaussienne
    double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * 3.141592 * u2);
    // Ajustement de l'écart-type
    return sig * z0;
}
