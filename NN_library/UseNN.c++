#ifndef CTE_UseNN
#define CTE_UseNN

#include "UseNN.h++"
#include <stdlib.h>

#endif

void forward1Layer (layer* previous, layer* next){
    int n = next -> nbNeurons;
    int m = previous -> nbNeurons;
}

void forwardPass (network NN, double* in, double* out){
    layer* past = NULL;
    layer* future = NN.input;
    // rentre l'entrée dans la première couche
    for(int i = 0; i < (future -> nbNeurons); i++){
        (future -> Neurons)[i].y = in[i];
    }
    // passe les couches une par une
    for(int i = 0; i < NN.nbLayer -1; i++){
        past = future;
        future = past -> next;
        forward1Layer(past, future);
    }
    for(int i = 0; i < (future -> nbNeurons); i++){
        out[i] = (future -> Neurons)[i].y;
    }
}

