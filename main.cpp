#include <iostream>
#include "NN_library\TeachNN.hpp"
#include <math.h>
#include <bibli_fonction.h>
#include <fstream>

using namespace std;
int nbPointTest = 100;
int nbPassage = 100;

double*** createBatch();
double*** createTest();


int main(){
    // Création du réseau
    network NN; 
    NN.nbLayer = 0;
    int nbHiddenLayer = 3;
    int* nbNeuron = (int*)malloc(nbHiddenLayer*sizeof(int));
    for(int i = 0; i < nbHiddenLayer; i++){
        nbNeuron[i] = 3;
    }
    addLayer(&NN, 1, Relu, dRelu, equiproba);
    fullyConnected(&NN, nbHiddenLayer, nbNeuron, Relu, dRelu, equiproba);
    addLayer(&NN, 1, Relu, dRelu, equiproba);

    // Apprentissage
    double * LBatch = (double*)malloc(nbPointTest*sizeof(double));
    double * LTest = (double*)malloc(nbPointTest*sizeof(double));
    double*** Batch = createBatch();
    double*** Test = createTest();
    for(int i = 0; i < 100; i++){
        trainNN0(&NN, nbPointTest, Batch, 0.0001, nbPassage);
        LBatch[i] = testBatch(&NN, nbPointTest, Batch);
        LTest[i] = testBatch(&NN, nbPointTest, Test);
        cout << LBatch[i] << "   " << LTest[i] << endl;
    }

    // Affichage du cos
    fstream fich;
    fich.open("donnees.dat", ios::out);
    for (int i = 0; i < 1000; i++){
        double a = 2 * 3.1411593 * i / 1000;
        double b = 0;
        forwardPass(&NN, &a, &b);
        fich << a << "  " << b << endl;
    }
    fich.close();
	ostringstream pyth;
	pyth
		<<"A = loadtxt('donnees.dat')\n"
		<<"x = A[:,0]\n"
        <<"y = A[:,1]\n"
		<<"plot(x,y)\n";
	make_plot_py(pyth);

    // Libérer la place allouer dynamiquement
    destroyNN(&NN);
    return 0;
}

double*** createBatch(){
    double*** Batch = (double***)malloc(nbPointTest*sizeof(double**));
    for(int i = 0; i < nbPointTest; i++){
        Batch[i] = (double**)malloc(2 * sizeof(double*));
        Batch[i][0] = (double*)malloc(sizeof(double));
        Batch[i][1] = (double*)malloc(sizeof(double));
        Batch[i][0][0] = 2 * 3.141593 * i / nbPointTest;
        Batch[i][1][0] = cos(Batch[i][0][0]);
    }
    return Batch;
}

double*** createTest(){
    double*** Batch = (double***)malloc(nbPointTest*sizeof(double**));
    for(int i = 0; i < nbPointTest; i++){
        Batch[i] = (double**)malloc(2 * sizeof(double*));
        Batch[i][0] = (double*)malloc(sizeof(double));
        Batch[i][1] = (double*)malloc(sizeof(double));
        Batch[i][0][0] = 2 * 3.141593 * (i + 0.5)/ nbPointTest;
        Batch[i][1][0] = cos(Batch[i][0][0]);
    }
    return Batch;
}