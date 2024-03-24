#include "TeachNN.hpp"
#include <stdlib.h>
#include <math.h>

double MSE(int nbVal, double* valNN, double* valTab){
    double x = 0;
    for(int i = 0; i < nbVal; i++){
        x += (valNN[i] - valTab[i]) * (valNN[i] - valTab[i]);
    }
    x /= nbVal;
    return x;
}

double Loss(int nbVal, double* valNN, double* dValNN, double* valTab, double* in){
    double x = 0;
    // espace pour rentrer le système d'équation
    for(int i = 0; i < nbVal; i++){
        x += (dValNN[i] - valNN[i]) * (dValNN[i] - valNN[i]);
    }
    // choix de la condition initial
    double z;
    if (in[0] < 0.1){
        for(int i = 0; i < nbVal; i++){
            z += (valNN[i] - 1) * (valNN[i] - 1);
        }
    }
    // Prise en compte de variables expérimentales
    // double y = MSE(nbVal, valNN, valTab);
    // Doser la contribution des trois ici
    return (0.5*x + z);
}

double test1Val(network* NN, double* in, double* outTab){
    int nbVal = NN->output -> nbNeurons;
    double* dOut = (double*)malloc(nbVal*sizeof(double));
    double* out = (double*)malloc(nbVal*sizeof(double));
    forwardPass(NN, in, out, dOut);
    double x = Loss(nbVal, out, dOut, outTab, in);
    free(out);
    free(dOut);
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
        double ddL = 0;
        // Ajoute la contribution au gradient de chaque neuronne de la couche suivante
        for(int j = 0; j < n; j++){
            dL += (prev->W)[j][i].val * (next->Neurons)[j].dL;
            ddL += (prev->W)[j][i].val * (next->Neurons)[j].ddL;
        }
        //prends en compte l'influence de la fonction d'activation
        dL *= (prev->Neurons)[i].dActiv((prev->Neurons)[i].y);
        ddL *= (prev->Neurons)[i].dActiv((prev->Neurons)[i].y);
        (prev -> Neurons)[i].dL = dL;
        (prev -> Neurons)[i].ddL = ddL;
    }
    // Mise à jour dérivé de L par rapport au poid
    for(int j = 0; j < n; j++){
        (prev->b)[j].dLdval += (next->Neurons)[j].dL;
        for(int i = 0; i < N; i++){
            (prev->W)[j][i].dLdval += (next->Neurons)[j].dL * (prev->Neurons)[i].activ((prev->Neurons)[i].y); //p3 samsung note
            //p5 samsung notes
            (prev->W)[j][i].dLdval += (next->Neurons)[j].ddL * (prev->Neurons)[i].dActiv((prev->Neurons)[i].y) * (prev->Neurons)[i].dy;
        }
    }
}
 
double backAllNN(network* NN, double* in, double* outTab){
    //initialisation et calcul d'une valeur de sortie
    layer* prev = NN -> output;
    layer* next;
    double* out = (double*)malloc((prev->nbNeurons)*sizeof(double));
    double* dout = (double*)malloc((prev->nbNeurons)*sizeof(double));
    forwardPass(NN, in, out, dout);
    double L = Loss(prev->nbNeurons, out, dout, outTab, in);
    // Calcul la dérivé pour la première couche, méthode non anlaytique pour la dérivée afin de prendre plus de forme de L en compte
    for(int i = 0; i < (prev->nbNeurons); i++){
        double epsilon = fabs(out[i]) * 0.0001;
        out[i] += epsilon;
        double Loffset = Loss(prev->nbNeurons, out, dout, outTab, in);
        (prev -> Neurons)[i].dL = (Loffset - L) / epsilon;
        out[i] -= epsilon;
        epsilon = fabs(dout[i]) * 0.0001;
        dout[i] += epsilon;
        double Loffset = Loss(prev->nbNeurons, out, dout, outTab, in);
        (prev -> Neurons)[i].ddL = (Loffset - L) / epsilon;
        dout[i] -= epsilon;
    }
    free(out);
    free(dout);
    // Remonte tout le réseau couche par couche (n-1 intervals car output n'a pas à être traité)
    for(int k = 1; k < (NN -> nbLayer); k++){
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
        Lay = Lay -> previous;
        for(int j = 0; j < Lay->next->nbNeurons; j++){
            (Lay->b)[j].dLdval /= sizeBatch;
            for(int i = 0; i < Lay->nbNeurons; i++){
                (Lay->W)[j][i].dLdval /= sizeBatch;
            }
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
        // Mise à jour des poids et remise à zéro des dLdval pour le prochain passage
        for (int i = 0; i < next->nbNeurons; i++){
            (prev -> b)[i].val -= alpha * (prev -> b)[i].dLdval;
            (prev -> b)[i].dLdval = 0;
            for(int j = 0; j < prev -> nbNeurons; j++){
                (prev -> W)[i][j].val -= alpha * (prev -> W)[i][j].dLdval;
                (prev -> W)[i][j].dLdval = 0;
            }
        }
    }
}

void updateWeightAdam(network* NN, double alpha, double beta, double gamma){
    double epsilon = 0.000000001; //evite les divisions par zéro
    // Evite de recalculer ces constantes à chaque fois
    double correcGamma = 1;
    double correcBeta = 1;
    if (NN->t < 100){
        correcGamma -= pow(gamma, NN->t);
    }
    if (NN->t < 1000){
        correcBeta -= pow(beta, NN->t);
    }
    layer* prev = NN -> output;
    layer* next;
    for(int k = 1; k < (NN -> nbLayer); k++){
        next = prev;
        prev = (next->previous);
        for (int i = 0; i < next->nbNeurons; i++){
            // La modification progressive de m permet de suivre le moment de la descente de gradient
            (prev->b)[i].m *= gamma / correcGamma;
            (prev->b)[i].m += ((1 - gamma) / correcGamma) * (prev->b)[i].dLdval;
            // La modification progressive de nu permet de réduire progressivement le poid
            (prev->b)[i].nu *= beta / correcBeta;
            (prev->b)[i].nu += ((1 - beta)/correcBeta) * (prev->b)[i].dLdval * (prev->b)[i].dLdval;
            // Mise à jour des poids et remise à zéro des dLdval pour le prochain passage
            (prev->b)[i].val -= alpha * (prev->b)[i].m / (sqrt((prev->b)[i].nu) + epsilon);
            (prev->b)[i].dLdval = 0;
            for(int j = 0; j < prev -> nbNeurons; j++){
                (prev -> W)[i][j].m *= gamma / correcGamma;
                (prev->W)[i][j].m += ((1 - gamma) / correcGamma) * (prev->W)[i][j].dLdval;
                (prev->W)[i][j].nu *= beta / correcBeta;
                (prev->W)[i][j].nu += ((1 - beta) / correcBeta) * (prev->W)[i][j].dLdval * (prev->W)[i][j].dLdval;
                (prev->W)[i][j].val -= alpha * (prev->W)[i][j].m / (sqrt((prev->W)[i][j].nu) + epsilon);
                (prev->W)[i][j].dLdval = 0;
            }
        }
    }
    NN->t++;
}

void trainNN0(network* NN, int sizeBatch, double*** batch, double alpha, int nbPassage){
    for(int m = 0; m < nbPassage; m++){
        backAndForthBatch(NN, sizeBatch, batch);
        updateWeightCte(NN, alpha);
    }
}

void trainNNAdam(network* NN, int sizeBatch, double*** batch, double alpha, double beta, double gamma, int nbPassage){
    for(int m = 0; m < nbPassage; m++){
        backAndForthBatch(NN, sizeBatch, batch);
        updateWeightAdam(NN, alpha, beta, gamma);
    }
}


