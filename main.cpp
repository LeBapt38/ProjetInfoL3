#include <iostream>
#include "NN_library\TeachNN.hpp"

using namespace std;


int main(){
    network NN; 
    NN.nbLayer = 0;
    addLayer(&NN, 2, Relu, dRelu, equiproba);
    // puis test des différentes composantes.
    return 0;
}