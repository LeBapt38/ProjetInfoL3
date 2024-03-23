#include <iostream>
#include "NN_library/TeachNN.hpp"
#include <math.h>
#include <bibli_fonctions.h>
#include <fstream>

using namespace std;
int nbPointTest = 100;
int nbPassage = 10;

double*** createBatch();
double*** createTest();

int main(){
    // Création du réseau
    network NN; 
    NN.nbLayer = 0;
    int nbHiddenLayer = 3;
    int* nbNeuron = (int*)malloc(nbHiddenLayer*sizeof(int));
    for(int i = 0; i < nbHiddenLayer; i++){
        nbNeuron[i] = 50;
    }
    addLayer(&NN, 1, Selu, dSelu, normal);
    fullyConnected(&NN, nbHiddenLayer, nbNeuron, Selu, dSelu, normal);
    addLayer(&NN, 1, Selu, dSelu, normal);
    free(nbNeurons);

    // Apprentissage
    double * LBatch = (double*)malloc(1000*sizeof(double));
    double * LTest = (double*)malloc(1000*sizeof(double));
    double*** Batch = createBatch();
    double*** Test = createTest();
    for(int i = 0; i < 1000; i++){
        trainNNAdam(&NN, nbPointTest, Batch, 0.01, 0.99, 0.9, nbPassage);
        LBatch[i] = testBatch(&NN, nbPointTest, Batch);
        LTest[i] = testBatch(&NN, nbPointTest, Test);
        cout << LBatch[i] << "   " << LTest[i] << "  "
        << (NN.output -> previous -> b)[0].val << "  "
        << (NN.output -> previous -> W)[0][0].val << endl;
        if (i > 100 && abs(LBatch[i-1] - LBatch[i]) < 1e-8 && abs(LTest[i-1] - LTest[i]) < 1e-6){
            break;            
        }
    }
    free(LBatch);
    free(LTest);

    // Affichage du x^2
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
    for(int i = 0; i < nbPointTest; i++){
        free(Batch[i][0]);
        free(Batch[i][1]);
        free(Batch[i]);
        free(Test[i][0]);
        free(Test[i][1]);
        free(Test[i]);
    }
    free(Batch);
    free(Test);
    return 0;
}

double*** createBatch(){
    double*** Batch = (double***)malloc(nbPointTest*sizeof(double**));
    for(int i = 0; i < nbPointTest; i++){
        Batch[i] = (double**)malloc(2 * sizeof(double*));
        Batch[i][0] = (double*)malloc(sizeof(double));
        Batch[i][1] = (double*)malloc(sizeof(double));
        Batch[i][0][0] = 2 * 3.141593 * i / nbPointTest;
        double incertitude = 0.5 - drand48();
        Batch[i][1][0] = Batch[i][0][0] * Batch[i][0][0] + 2 + incertitude;
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
        Batch[i][1][0] = Batch[i][0][0] * Batch[i][0][0] + 2;
    }
    return Batch;
}