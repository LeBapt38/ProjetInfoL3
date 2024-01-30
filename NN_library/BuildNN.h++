#include "ActivationFun.h++"


// Sructure contenant la forme de base d'un neuronne.
typedef struct{
    double y;
    double dLdy;
    double (*activ)(double);
    double (*dActiv)(double);
}neuron;

// Structure contenant la forme d'une couche de neuronne à l'intérieur de la liste doublement chainé à la base du réseau.
typedef struct layer layer;
struct layer{
    layer* next;
    layer* previous;
    int nbNeurons;
    neuron* Neurons;
    double** W;
    double* b;
};

// Structure contenant l'entrée et la sortie du réseau.
typedef struct {
    layer* input;
    layer* output;
    int nbLayer;
}network;

// Fonction construisant une couche du réseau
layer* buildLayer(int nbNeur, double(*g)(double), double(*dg)(double));

// Fonction ajoutant une nouvelle couche à la fin du réseau.
void addLayer(network NN, int nbNeur, double(*g)(double), double(*dg)(double));