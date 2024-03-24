#include "UseNN.hpp"


// Calcule l'écart moyen quadratique entre deux tableaux de taille nbVal
double MSE(int nbVal, double* valNN, double* valTab);

// Définition de la fonction de cout dans le cas général
double Loss(int nbVal, double* valNN, double* dValNN, double* valTab, double* in);

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

// Met à jour les poids avec la méthode Adam
void updateWeightAdam(network* NN, double alpha, double beta, double gamma);

// Première fonction permettant d'entrainer un réseau de neuronne : 
// - alpha constant 
// - nb de passage choisie à l'avance
void trainNN0(network* NN, int sizeBatch, double*** batch, double alpha, int nbPassage);

// Entrainement du réseau en utilisant la méthode Adam
void trainNNAdam(network* NN, int sizeBatch, double*** batch, double alpha, double beta, double gamma, int nbPassage);
