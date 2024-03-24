
#include "ActivationFun.hpp"
#include "Random.hpp"



// Sructure contenant la forme de base d'un neuronne.
typedef struct{
    double y;
    double dy;
    double dL; //gardera la valeur en cours lors de la remonté de la dépendance en y
    double ddL; // de même pour la dépendance en dy
    double (*activ)(double);
    double (*dActiv)(double);
}neuron;

// Structure contenant les poids
typedef struct{
    double val;
    double dLdval;
    double m;
    double nu;
}weight;

// Structure contenant la forme d'une couche de neuronne à l'intérieur de la liste doublement chainé à la base du réseau.
typedef struct layer layer;
struct layer{
    layer* next;
    layer* previous;
    int nbNeurons;
    neuron* Neurons;
    weight** W;
    weight* b;
};

// Structure contenant l'entrée et la sortie du réseau.
typedef struct {
    layer* input;
    layer* output;
    int nbLayer;
    int t;   //Contiendra le nombre de passage lors de l'apprentissage 
}network;

// Fonction construisant une couche du réseau
layer* buildLayer(int nbNeur, double(*g)(double), double(*dg)(double));

// Fonction ajoutant une nouvelle couche à la fin du réseau.
void addLayer(network* NN, int nbNeur, double(*g)(double), double(*dg)(double), double (*random)(int, int, double(*g)(double)));

// Construit ou ajoute un réseau de neuronne complétement connecter.
void fullyConnected(network* NN, int nbLayer, int* nbNeuron, double(*g)(double), double(*dg)(double), double (*random)(int, int, double(*g)(double)));

// Libère la place mémoire prise par les variables définit à la main
void destroyNN(network* NN);


