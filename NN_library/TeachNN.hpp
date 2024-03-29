#include "UseNN.hpp"


// Calcule l'écart moyen quadratique entre deux tableaux de taille nbVal
double MSE(int nbVal, double* valNN, double* valTab);

// Donne l'erreur quadratique pour une valeur tabulé
double test1Val(network* NN, double* in, double* outTab);

// Donne l'erreur quadatique moyen sur un batch, utile pour le set de validation
double testBatch(network* NN, int sizeBatch, double*** batch);

// Remonte le gradient de une couche
void back1Layer(layer* prev, layer* next);

// Remonte tout le NN en mettant à jour les gradients
double backAllNN(network* NN, double* in, double* outTab);

// Utilise le batch pour calculer l'espérance des gradients, renvoie la valeur moyenne de L
double backAndForthBatch(network* NN, int sizeBatch, double*** batch);

// Met à jour les poids avec une vitesse d'apprentissage alpha constante
void updateWeightCte(network* NN, double alpha);

// Première fonction permettant d'entrainer un réseau de neuronne : 
// - alpha constant 
// - nb de passage choisie à l'avance
void trainNN0(network* NN, int sizeBatch, double*** batch, double alpha, int nbPassage);

