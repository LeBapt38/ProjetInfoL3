# Projet d'informatique L3

 ## Abstract
 The idea is to create a relatively simple library for Neural networks in C. The aim is to use it to solve relatively simple PDE in physics. The first version will only tackle one dimension input. Later on, a method to deal with 2D and 3D would be a nice addition.

 ## Objectif du projet
 1. Se familiariser avec le fonctionnement d'un réseau de neuronne adapté pour des approximations de fonction.
 2. S'habituer à utiliser git et github pour le développement d'un projet. 
 3. Continuer de prendre en main le C.

 ## Cahier des charges
 L'objectif étant de construire une bibliothèque pour faire des réseaux de neuronnes et pas de construire un réseau en particulier, elle devra permettre :

 1. De modifier aisément les hyperparamètres du réseau (nombre de couche, nombre de neuronnes par couche, fonction d'activation).
 2. De construire les architectures classiques (complètement relié, fonctions d'activation ReLU et tanh, réseau convolutif??)
 3. Laisse la possibiliité de choisir la fonction de cout.

 L'objectif principale étant de créé des PINNs, le bibliothèque devra aussi permettre :

 4. D'accéder aux dérivées partielles.
 5. De donner une solution pour l'affichage graphique.

 ## Fonctionnement des fonctions

 ### Fichier BuildNN
Fichier contenant les fonctions permettant de construire le réseau de neuronne couche par couche ou de manière automatisé pour un réseau complètement connecté. 
A modifié pour prendre en colmpte un réseau convolutif.

 Lors de la définition de W, *W[i][j]* correspond au poid de la liaison entre le neuronne j de la couche précédente vers le neuronne i de la couche suivante.

### Fichier Random
Contient les fonctions permettant d'initialiser le poids de manière aléatoire. La fonction pour une répartition équiprobable suivant les lignes directrices de [1] déjà codé. 
Potentiellement rajouter celle pour une distribution gaussienne.

### Fichier ActivationFun
Contient les différentes fonctions d'activation ainsi que leur dérivées. Pour l'instant la fonction Relu est codé. Rajouter tanh...

### Fichier UseNN
Contient les fonctions nécessaires pour utiliser le réseau de neuronne.