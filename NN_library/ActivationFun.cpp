#include "ActivationFun.hpp"
#include <math.h>

double Relu (double x){
    double y = 0;
    if(x > 0){y = x;}
    return y;
}

double dRelu (double x){
    double y = 0;
    if(x > 0){y = 1;}
    return y;
}

double Selu (double x){
    double y = 0;
    if(x >= 0){
        y = 1.0507 * x;
    }
    else{
        y = 1.0507 * 1.6733 * (exp(x) - 1);
    }
    return y;
}

double dSelu (double x){
    double y = 0;
    if(x >= 0){
        y = 1.0507;
    }
    else{
        y = 1.0507 * 1.6733 * exp(x);
    }
    return y;
}
