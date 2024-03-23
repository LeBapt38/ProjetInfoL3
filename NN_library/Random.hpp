#include "ActivationFun.hpp"

// Tirage d'une valeur aléatoire pour une matrice de poid selon une ditribution : 
// - equiprobable
double equiproba(int previous, int next, double(*g)(double));

// - normal
double normal(int previous, int next, double(*g)(double));

double Gaussian(double sig);