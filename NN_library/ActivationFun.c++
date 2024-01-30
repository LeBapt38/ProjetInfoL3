#include "ActivationFun.h++"

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