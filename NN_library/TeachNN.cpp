#include "TeachNN.hpp"
#include <stdlib.h>

double MSE(int nbVal, double* valNN, double* valTab){
    double x = 0;
    for(int i = 0; i < nbVal; i++){
        x += (valNN[i] - valTab[i]) * (valNN[i] - valTab[i]);
    }
    x /= nbVal;
    return x;
}

double test1Val(network* NN, double* in, double* outTab){
    int nbVal = NN->output -> nbNeurons;
    double* out = (double*)malloc(nbVal*sizeof(double));
    forwardPass(NN, in, out);
    double x = MSE(nbVal, out, outTab);
    free(out);
    return x;
}

double testBatch(network* NN, int sizeBatch, double*** batch){
    double x = 0;
    for(int i = 0; i < sizeBatch; i++){
        x += test1Val(NN, batch[i][0], batch[i][1]);
    }
    x /= sizeBatch;
    return x;
}

void back1Layer(layer* prev, layer* next){
    int N = (prev -> nbNeurons);
    int n = (next->nbNeurons);
    // Calcul la dérivé partielle neuronne par neuronne.
    for (int i = 0; i < N; i++){
        double dL = 0;
        // Ajoute la contribution au gradient de chaque neuronne de la couche suivante
        for(int j = 0; j < n; j++){
            dL += (prev->W)[j][i] * (next->Neurons)[j].dL;
        }
        //prends en compte l'influence de la fonction d'activation
        dL *= (prev->Neurons)[i].dActiv((prev->Neurons)[i].y);
        (prev->Neurons)[i].dLdy += dL;
        (prev->Neurons)[i].ydLdy += (prev->Neurons)[i].y * dL;
        (next -> Neurons)[i].dL = dL;
    }
}
 
double backAllNN(network* NN, double* in, double* outTab){
    //initialisation et calcul d'une valeur de sortie
    layer* prev = NN -> output;
    layer* next;
    double* out = (double*)malloc((prev->nbNeurons)*sizeof(double));
    forwardPass(NN, in, out);
    double L = MSE(prev->nbNeurons, out, outTab);
    // Calcul la dérivé pour la première couche
    for(int i = 0; i < (prev->nbNeurons); i++){
        double dL = 2 * out[i] * (out[i] - outTab[i]);
        (prev->Neurons)[i].dLdy += dL;
        (prev -> Neurons)[i].dL = dL;
    }
    free(out);
    // Remonte tout le réseau couche par couche (n-2 intervals car input n'a pas à être traité)
    for(int k = 1; k < (NN -> nbLayer)-1; k++){
        next = prev;
        prev = (next->previous);
        back1Layer(prev, next);
    }
    return L;
}

double backAndForthBatch(network* NN, int sizeBatch, double*** batch){
    double L = 0;
    // Utilise le batch pour calculer le gradient
    for(int l = 0; l < sizeBatch; l++){
        L += backAllNN(NN, batch[l][0], batch[l][1]);
    }
    layer* Lay = NN -> output;
    // Permet d'obtenir l'espérance et pas la somme
    for(int k = 1; k < NN -> nbLayer; k++){
        for(int i = 0; i < Lay->nbNeurons; i++){
            (Lay->Neurons)[i].dLdy /= sizeBatch;
            (Lay->Neurons)[i].ydLdy /= sizeBatch;
        }
    }
    L /= sizeBatch;
    return L;
}

void updateWeightCte(network* NN, double alpha){
    layer* prev = NN -> output;
    layer* next;
    for(int k = 1; k < (NN -> nbLayer); k++){
        next = prev;
        prev = (next->previous);
        for (int i = 0; i < next->nbNeurons; i++){
            (prev -> b)[i] -= alpha * (next->Neurons)[i].dLdy;
            for(int j = 0; j < prev -> nbNeurons; j++){
                double x = ((next -> Neurons)[i].ydLdy - (prev -> b)[i] * (next -> Neurons)[i].dLdy);
                (prev -> W)[i][j] = (alpha / (prev -> W)[i][j]) * x;
            }
        }
    }
}

void trainNN0(network* NN, int sizeBatch, double*** batch, double alpha, int nbPassage){
    for(int m = 0; m < nbPassage; m++){
        backAndForthBatch(NN, sizeBatch, batch);
        updateWeightCte(NN, alpha);
    }
}

