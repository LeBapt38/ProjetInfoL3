#ifndef CTE_BuildNN
#define CTE_BuildNN

#include <stdlib.h>
#include "BuildNN.h++"

#endif
using namespace std;

layer* buildLayer(int nbNeur, double(*g)(double), double(*dg)(double)){
    layer* newLayer;
    newLayer -> next = NULL;
    newLayer -> previous = NULL;
    newLayer -> W = NULL;
    newLayer -> b = NULL;
    newLayer -> nbNeurons = nbNeur;
    newLayer -> Neurons = (neuron*)malloc(nbNeur*sizeof(neuron));
    //initialise les neurones à 0 avec la fonction d'activation choisie pour la couche.
    for(int i = 0; i<nbNeur; i++){
        (newLayer -> Neurons) [i].y =0;
        (newLayer -> Neurons) [i].dLdy = 0;
        (newLayer -> Neurons) [i].activ = g;
        (newLayer -> Neurons) [i].dActiv = dg;
    }
    return newLayer;
}

void addLayer(network NN, int nbNeur, double(*g)(double), double(*dg)(double)){
    layer* newLayer = buildLayer(nbNeur, g, dg); // crée la nouvelle couche
    // met à jour toutes les nouvelles adresses
    if(NN.nbLayer == 0){
        NN.input = newLayer;
        NN.output = newLayer;
    }else{
        layer* oldLayer = NN.output;
        oldLayer -> next = newLayer;
        newLayer -> previous = NN.output;
        NN.output = newLayer;
        // définie W et b entre les deux couches
        oldLayer -> b = (double*)malloc((newLayer->nbNeurons) * sizeof(double));
        oldLayer -> W = (double**)malloc((newLayer->nbNeurons) * sizeof(double));
        for(int i = 0; i < (newLayer -> nbNeurons); i++){
            (oldLayer -> W)[i] = (double*)malloc((oldLayer -> nbNeurons));
            (oldLayer -> b)[i] = 0;
            for(int j = 0; j < (oldLayer -> nbNeurons); j++){
                (oldLayer -> W)[i][j] = 0;
            }
        }
    }
    NN.nbLayer++;
}

