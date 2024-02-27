#ifndef CTE_UseNN
#define CTE_UseNN

#include "UseNN.hpp"
#include <stdlib.h>

#endif

// fonction à modifier pour une couche convolutive.
void forward1Layer (layer* previous, layer* next){
    int n = next -> nbNeurons;
    int m = previous -> nbNeurons;
    for (int i = 0; i < n; i++){
        (next -> Neurons)[i].y = (previous -> b)[i].val;
        // Ajoute les valeurs transmise par les neuronnes précédents.
        for (int j = 0; j < m; j++){
            (next -> Neurons)[i].y += (previous -> W)[i][j].val * (previous -> Neurons)[j].activ((previous -> Neurons)[j].y);
        }
    }
}

void forwardPass (network* NN, double* in, double* out){
    layer* past = NULL;
    layer* future = NN->input;
    // Rentre l'entrée dans la première couche
    for(int i = 0; i < (future -> nbNeurons); i++){
        (future -> Neurons)[i].y = in[i];
    }
    // Passe les couches une par une
    for(int i = 0; i < NN->nbLayer -1; i++){
        past = future;
        future = past -> next;
        forward1Layer(past, future);
    }
    //Atribue la valeur calculer à la variable de sortie
    for(int i = 0; i < (future -> nbNeurons); i++){
        out[i] = (future -> Neurons)[i].y;
    }
}

