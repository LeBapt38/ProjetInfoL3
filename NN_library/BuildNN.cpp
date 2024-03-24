#ifndef CTE_BuildNN
#define CTE_BuildNN

#include <stdlib.h>
#include "BuildNN.hpp"

#endif
using namespace std;

layer* buildLayer(int nbNeur, double(*g)(double), double(*dg)(double)){
    layer* newLayer = (layer*)malloc(sizeof(layer));
    newLayer -> next = NULL;
    newLayer -> previous = NULL;
    newLayer -> W = NULL;
    newLayer -> b = NULL;
    newLayer -> nbNeurons = nbNeur;
    newLayer -> Neurons = (neuron*)malloc(nbNeur*sizeof(neuron));
    //initialise les neurones à 0 avec la fonction d'activation choisie pour la couche.
    for(int i = 0; i < nbNeur; i++){
        (newLayer -> Neurons) [i].y =0;
        (newLayer -> Neurons) [i].dy =0;
        (newLayer -> Neurons) [i].dL = 0;
        (newLayer -> Neurons) [i].ddL = 0;
        (newLayer -> Neurons) [i].activ = g;
        (newLayer -> Neurons) [i].dActiv = dg;
    }
    return newLayer;
}

void addLayer(network* NN, int nbNeur, double(*g)(double), double(*dg)(double), double (*random)(int, int, double(*g)(double))){
    layer* newLayer = buildLayer(nbNeur, g, dg); // crée la nouvelle couche
    // met à jour toutes les nouvelles adresses
    if(NN->nbLayer == 0){
        NN->input = newLayer;
        NN->output = newLayer;
    }else{
        layer* oldLayer = NN->output;
        oldLayer -> next = newLayer;
        newLayer -> previous = NN->output;
        NN->output = newLayer;
        // définie W et b entre les deux couches
        oldLayer -> b = (weight*)malloc((newLayer->nbNeurons) * sizeof(weight));
        oldLayer -> W = (weight**)malloc((newLayer->nbNeurons) * sizeof(weight));
        for(int i = 0; i < (newLayer -> nbNeurons); i++){
            (oldLayer -> W)[i] = (weight*)malloc((oldLayer -> nbNeurons) * sizeof(weight));
            (oldLayer -> b)[i].val = 0;
            (oldLayer -> b)[i].dLdval = 0;
            for(int j = 0; j < (oldLayer -> nbNeurons); j++){
                (oldLayer -> W)[i][j].val = random(oldLayer -> nbNeurons, newLayer -> nbNeurons, g);
                (oldLayer -> W)[i][j].dLdval = 0;
                (oldLayer -> W)[i][j].m = 0;
                (oldLayer -> W)[i][j].nu = 0;
            }
        }
    }
    NN->nbLayer++;
}

void fullyConnected(network* NN, int nbLayer, int* nbNeuron, double(*g)(double), double(*dg)(double), double (*random)(int, int, double(*g)(double))){
    for(int i = 0; i < nbLayer; i++){
        addLayer(NN, nbNeuron[i], g, dg, random);
    }
}

void destroyNN(network* NN){
    layer* LL = NN->input;
    layer* L;
    //traite les N-1 couches initialiser avec leur W et b
    for (int i = 1; i < NN->nbLayer; i++){
        L = LL;
        LL = L -> next;
        free(L -> b);
        for(int j = 0; j < LL-> nbNeurons; j++){
            free((L -> W)[j]);
        }
        free(L -> W);
        free(L -> Neurons);
        free(L);
    }
    // Libère le dernier tableau de neuronne
    free(LL -> Neurons);
    free(LL);
}

